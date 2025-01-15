local m, s, o

m = Map("lvgl-sysinfo", "LVGL SysInfo Settings", "Configure display mode and screen settings.")

s = m:section(TypedSection, "settings", "Settings")
s.anonymous = true
s.addremove = false

-- Display Mode Option
o = s:option(ListValue, "display_mode", "Display Mode", "Select the display mode for the LVGL SysInfo.")
o:value("system", "System")
o:value("modem", "Modem")
o.default = "modem"

-- Screen Enabled Option
o = s:option(Flag, "screen_enabled", "Enable Screen", "Toggle the screen on or off.")
o.default = "1"

return m
