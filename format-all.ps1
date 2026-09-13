#Requires -Version 5

# args
param (
    [string]$CF
)

$CF

if (!(Test-Path $CF -PathType Leaf)) {
    "Failed to locate clang-format.exe"
    Exit
}

$headers = Get-ChildItem "$PSScriptRoot\include" -Recurse -File -ErrorAction SilentlyContinue 
$src = Get-ChildItem "$PSScriptRoot\src" -Recurse -File -ErrorAction SilentlyContinue 

foreach ($file in $headers) {
    $file.BaseName
    & $CF -i -style=file $file
}

foreach ($file in $src) {
    $file.BaseName
    & $CF -i -style=file $file
}

"Formatted $($headers.Length) header files"
"Formatted $($src.Length) source files"