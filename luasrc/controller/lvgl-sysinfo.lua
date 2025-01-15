module("luci.controller.lvgl-sysinfo", package.seeall)

function index()
    entry({"admin", "system", "lvgl-sysinfo"}, cbi("lvgl-sysinfo/settings"), "LVGL SysInfo", 60).dependent = true
end