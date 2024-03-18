set_project("Guild Wars DAT Reader")
set_version("0.0.0")

add_rules("mode.debug", "mode.release")
set_languages("c++20")
set_optimize("fastest")
set_warnings("all", "error")

-- Packages
-- Function to add platform-specific flags
function add_platform_specific_flags()
    if is_plat("windows") then
        add_cxxflags("/EHsc")
        add_cxxflags("-D_WIN32_WINNT=0x0601")
    else
        -- Add flags for e.g. linux here
    end
end

add_requires("flatbuffers")
if is_cross() then -- requires xmake 2.8.8
    add_requires("flatbuffers~host", { host = true })
end

target("gw_dat_reader")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("flatbuffers")
    add_platform_specific_flags()
target_end()


-- Testing setup
add_requires("gtest", {configs = {main = false, gmock = true}})
add_requires("spdlog")
add_requires("flatbuffers")
if is_cross() then -- requires xmake 2.8.8
    add_requires("flatbuffers~host", { host = true })
end

-- Iterate over test files and create test targets
for _, file in ipairs(os.files("tests/test_*.cpp")) do
    local name = path.basename(file)
    target(name)
        set_kind("binary")
        add_packages("gtest", "spdlog", "flatbuffers")
        set_default(false)
        add_files(file)
        add_tests("default")
        add_platform_specific_flags()
end

-- Run flatc command to generate C++ code from .fbs files
local function get_flatc_cmd(target)
    local flatbuffers_installdir = target:pkg("flatbuffers"):installdir()
    local flatc_exe = is_plat("windows") and "flatc.exe" or "flatc"
    local flatc_path = path.join(flatbuffers_installdir, "bin", flatc_exe)

    local fbs_dir = path.join(os.scriptdir(), "flatbuffers", "schemes")
    local fbs_files = os.files(path.join(fbs_dir, "*.fbs"))
    
    local flatc_exe = is_plat("windows") and "flatc.exe" or "flatc"
    local flatc_path = path.join(flatbuffers_installdir, "bin", flatc_exe)
    
    local output_dir = path.join(os.scriptdir(), "flatbuffers", "output")
    
    local flatc_cmd = { flatc_path, "--cpp", "--grpc", "-o", output_dir }
    for _, fbs_file in ipairs(fbs_files) do
        table.insert(flatc_cmd, fbs_file)
    end
    
    -- Return as a string
    return table.concat(flatc_cmd, " ")
end

before_build(function (target)
    local flatc_cmd = get_flatc_cmd(target)
    --print("Running flatc command: " .. flatc_cmd, " ")
    os.run(flatc_cmd)
end)