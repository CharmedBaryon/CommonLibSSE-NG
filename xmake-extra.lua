local PLUGIN_FILE = [[
#include <SKSE/SKSE.h>
using namespace std::literals;
SKSEPluginInfo(
    .Version = { ${PLUGIN_VERSION_MAJOR}, ${PLUGIN_VERSION_MINOR}, ${PLUGIN_VERSION_PATCH}, 0 },
    .Name = "${PLUGIN_NAME}"sv,
    .Author = "${PLUGIN_AUTHOR}"sv,
    .SupportEmail = "${PLUGIN_EMAIL}"sv,
    .StructCompatibility = ${PLUGIN_STRUCT_COMPATIBILITY},
    .RuntimeCompatibility = ${PLUGIN_RUNTIME_COMPATIBILITY}
)]]

local PLUGIN_VERSION_FILE = [[
#include <winres.h>

1 VERSIONINFO
FILEVERSION ${PLUGIN_VERSION_MAJOR}, ${PLUGIN_VERSION_MINOR}, ${PLUGIN_VERSION_PATCH}, 0
PRODUCTVERSION ${PROJECT_VERSION_MAJOR}, ${PROJECT_VERSION_MINOR}, ${PROJECT_VERSION_PATCH}, 0
FILEFLAGSMASK 0x17L
#ifdef _DEBUG
    FILEFLAGS 0x1L
#else
    FILEFLAGS 0x0L
#endif
FILEOS 0x4L
FILETYPE 0x1L
FILESUBTYPE 0x0L
BEGIN
    BLOCK "StringFileInfo"
    BEGIN
        BLOCK "040904b0"
        BEGIN
            VALUE "FileDescription", "${PLUGIN_DESCRIPTION}"
            VALUE "FileVersion", "${PLUGIN_VERSION}.0"
            VALUE "InternalName", "${PLUGIN_NAME}"
            VALUE "LegalCopyright", "${PLUGIN_AUTHOR} | ${PLUGIN_LICENSE}"
            VALUE "ProductName", "${PROJECT_NAME}"
            VALUE "ProductVersion", "${PROJECT_VERSION}.0"
        END
    END
    BLOCK "VarFileInfo"
    BEGIN
        VALUE "Translation", 0x409, 1200
    END
END]]

-- Usage:
-- add_deps("commonlibsse-ng")
-- add_rules("commonlibsse-ng.plugin", {
--     name = "PluginName",
--     author = "Author Name",
--     description = "Plugin Description",
--     email = "example@site.com",
--     options = {
--         address_library = true,
--         signature_scanning = false,
--         struct_dependent = false
--     }
-- })

rule("commonlibsse-ng.plugin")
    add_deps("win.sdk.resource")

    on_config(function(target)
        import("core.base.semver")
        import("core.project.depend")
        import("core.project.project")

        target:set("arch", "x64")
        target:set("kind", "shared")

        local conf = target:extraconf("rules", "commonlibsse-ng.plugin")
        local conf_dir = path.join(target:autogendir(), "rules", "commonlibsse-ng", "plugin")

        local conf_opt_struct_compatibility = "SKSE::StructCompatibility::Independent"
        local conf_opt_runtime_compatibility = "SKSE::VersionIndependence::AddressLibrary"
        if conf.options then
            if conf.options.struct_dependent then
                conf_opt_struct_compatibility = "SKSE::StructCompatibility::Dependent"
            end

            if conf.options.address_library or conf.options.signature_scanning then
                if not conf.options.address_library then
                    conf_opt_runtime_compatibility = "SKSE::VersionIndependence::SignatureScanning"
                end
            end
        end

        local conf_map = {
            PLUGIN_AUTHOR                = conf.author or "",
            PLUGIN_DESCRIPTION           = conf.description or "",
            PLUGIN_EMAIL                 = conf.email or "",
            PLUGIN_LICENSE               = (target:license() or "Unknown") .. " License",
            PLUGIN_NAME                  = conf.name or target:name(),
            PLUGIN_STRUCT_COMPATIBILITY  = conf_opt_struct_compatibility,
            PLUGIN_RUNTIME_COMPATIBILITY = conf_opt_runtime_compatibility,
            PLUGIN_VERSION               = target:version() or "0.0.0",
            PLUGIN_VERSION_MAJOR         = semver.new(target:version() or "0.0.0"):major(),
            PLUGIN_VERSION_MINOR         = semver.new(target:version() or "0.0.0"):minor(),
            PLUGIN_VERSION_PATCH         = semver.new(target:version() or "0.0.0"):patch(),
            PROJECT_NAME                 = project.name() or "",
            PROJECT_VERSION              = project.version() or "0.0.0",
            PROJECT_VERSION_MAJOR        = semver.new(project.version() or "0.0.0"):major(),
            PROJECT_VERSION_MINOR        = semver.new(project.version() or "0.0.0"):minor(),
            PROJECT_VERSION_PATCH        = semver.new(project.version() or "0.0.0"):patch(),
        }

        local conf_parse = function(a_str)
            return a_str:gsub("(%${([^\n]-)})", function(_, a_var)
                local result = conf_map[a_var:trim()]
                if type(result) ~= "string" then
                    result = tostring(result)
                end
                assert(result ~= nil, "cannot get variable(%s)", a_var)
                return result
            end)
        end

        local add_file = function(a_path, a_data)
            local file_path = path.join(conf_dir, a_path)
            depend.on_changed(function()
                local file = io.open(file_path, "w")
                if file then
                    file:write(conf_parse(a_data), "\n")
                    file:close()
                end
            end, { dependfile = target:dependfile(file_path), files = project.allfiles()})
            target:add("files", file_path)
        end

        add_file("plugin.cpp", PLUGIN_FILE)
        add_file("version.rc", PLUGIN_VERSION_FILE)
    end)
