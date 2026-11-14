# Migration Guide: Adding Code Verification to Memory Patches

This guide helps you migrate existing `safe_write()` and `safe_fill()` calls to use verification for safer memory patching.

## Quick Reference

### Enable Audit Mode
Add to your CMakeLists.txt or compiler flags:
```cmake
target_compile_definitions(${PROJECT_NAME} PRIVATE REL_AUDIT_UNVERIFIED_PATCHES)
```

This will:
- Show compiler warnings for unverified calls (with `[[deprecated]]` attribute)
- Log runtime warnings for every unverified patch with location and size
- Help you identify which patches need verification

### Migration Patterns

#### Before (Unverified)
```cpp
// No verification - vulnerable to game updates
REL::safe_write(address, patch_data, sizeof(patch_data));
REL::safe_fill(address, REL::NOP, 7);
```

#### After (With Verification)
```cpp
// Method 1: Raw byte verification
std::uint8_t expected[] = { 0x48, 0x8B, 0x05, 0xF9, 0xAA, 0x10, 0x00 };
REL::safe_write(address, patch_data, sizeof(patch_data), expected, sizeof(expected));

// Method 2: PatternMatcher (recommended)
auto pattern = make_pattern<"48 8B 05 ?? ?? ?? ??">();
REL::safe_write(address, patch_data, sizeof(patch_data), pattern);

// Method 3: Using macros
auto pattern = make_pattern<"48 8B 05 F9 AA 10 00">();
VERIFY_AND_FILL(address, REL::NOP, 7, pattern, "Hook description");
```

## Step-by-Step Migration Process

### Step 1: Enable Audit Mode
1. Add `REL_AUDIT_UNVERIFIED_PATCHES` to your build
2. Compile and run your plugin
3. Check logs for all unverified patch locations

### Step 2: Gather Verification Data
For each logged patch location:
1. Use a debugger or disassembler to examine the memory at that address
2. Record the expected bytes before your patch
3. Choose appropriate verification method (raw bytes vs pattern)

### Step 3: Add Verification
Replace unverified calls with verified versions:

```cpp
// Example migration for a typical NOP patch
// Before:
REL::safe_fill(REL::RelocationID(12345, 67890).address() + 0x10, REL::NOP, 5);

// After: 
auto address = REL::RelocationID(12345, 67890).address() + 0x10;
auto pattern = make_pattern<"E8 ?? ?? ?? ?? 48">();  // call + mov
if (!REL::safe_fill(address, REL::NOP, 5, pattern)) {
    logger::error("Failed to patch function call at {:x}", address);
}
```

### Step 4: Test Across Game Versions
1. Test on different game versions (SE/AE/VR if applicable)
2. Verify patterns work with Address Library ID resolution
3. Update patterns if needed for cross-version compatibility

### Step 5: Disable Audit Mode
Once all patches are verified, remove `REL_AUDIT_UNVERIFIED_PATCHES` from your build.

## Best Practices

### Use PatternMatcher for Cross-Version Compatibility
```cpp
// Good: Wildcards handle address differences
auto pattern = make_pattern<"48 8B 05 ?? ?? ?? ??">();  // mov rax, [rip+offset]

// Bad: Hardcoded addresses break on updates  
std::uint8_t expected[] = { 0x48, 0x8B, 0x05, 0xF9, 0xAA, 0x10, 0x00 };
```

### Verify Instruction Boundaries
```cpp
// Good: Verify complete instruction
auto pattern = make_pattern<"48 8B 05 ?? ?? ?? ?? 48 89">();  // mov + mov
REL::safe_fill(address, REL::NOP, 7, pattern);  // NOP first instruction only

// Bad: Partial instruction verification
auto pattern = make_pattern<"48 8B 05">();  // Incomplete instruction
```

### Handle Verification Failures Gracefully
```cpp
auto pattern = make_pattern<"E8 ?? ?? ?? ??">();
if (!REL::safe_write(address, patch, sizeof(patch), pattern)) {
    logger::warn("Patch verification failed at {:x} - game may have updated", address);
    return false;  // Don't crash, just skip the patch
}
```

### Use Descriptive Logging
```cpp
// Good: Descriptive error messages
if (!REL::safe_fill(address, REL::NOP, 5, pattern)) {
    logger::error("Failed to disable texture streaming at {:x}", address);
}

// OK: Using macros (but less control over error handling)
VERIFY_AND_FILL(address, REL::NOP, 5, pattern, "Disable texture streaming");
```

## Common Patterns to Verify

### Function Call Patches
```cpp
// Pattern: E8 XX XX XX XX (call relative)
auto call_pattern = make_pattern<"E8 ?? ?? ?? ??">();
REL::safe_fill(call_address, REL::NOP, 5, call_pattern);
```

### Jump Patches  
```cpp
// Pattern: E9 XX XX XX XX (jmp relative) or EB XX (jmp short)
auto jmp_pattern = make_pattern<"E9 ?? ?? ?? ??">();
auto jmp_short_pattern = make_pattern<"EB ??">();
```

### Memory Access Patches
```cpp
// Pattern: 48 8B 05 XX XX XX XX (mov rax, [rip+offset]) 
auto mov_pattern = make_pattern<"48 8B 05 ?? ?? ?? ??">();
```

### Conditional Jumps
```cpp
// Pattern: 74 XX (je short) or 0F 84 XX XX XX XX (je near)
auto je_short_pattern = make_pattern<"74 ??">();
auto je_near_pattern = make_pattern<"0F 84 ?? ?? ?? ??">();
```

## Troubleshooting

### "Pattern verification failed"
1. Check if game version matches expected pattern
2. Verify Address Library ID is correct for your game version
3. Use wildcards for variable portions (addresses, offsets)
4. Check if instruction boundaries are respected

### "Code verification size mismatch" 
- You're trying to verify more bytes than you're patching
- This usually indicates a logic error in your verification approach

### Compile-time deprecation warnings
- Normal during migration - they identify unverified patches
- Each warning shows a location that needs verification added
- Warnings disappear once you add verification or disable audit mode

## Performance Considerations

Verification adds minimal overhead:
- **Compile-time**: Pattern validation catches errors early
- **Runtime**: Simple memcmp for verification (nanoseconds)
- **Memory**: No additional memory usage after initialization

The safety benefits far outweigh the minimal performance cost.