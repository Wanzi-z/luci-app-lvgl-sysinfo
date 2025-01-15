
include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-lvgl-sysinfo
PKG_VERSION:=1.0
PKG_RELEASE:=1
PKG_SOURCE_PROTO:=git
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_LICENSE:=GPL
PKG_LICENSE_FILES:=LICENSE
PKG_MAINTAINER:=Fish <ss@ss8.io>

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=luci
  CATEGORY:=LuCI
  SUBMENU:=3. Applications
  TITLE:=LVGL System Information Display
endef

define Package/$(PKG_NAME)/description
A system information display using LVGL for framebuffer on OpenWrt.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	cp -r ./src $(PKG_BUILD_DIR)/
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR)/src \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)"
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/h29k_sysinfo $(1)/usr/bin/h29k_sysinfo

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./root/etc/init.d/h29k-sysinfo $(1)/etc/init.d/h29k-sysinfo

	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/controller
	$(CP) ./luasrc/controller/lvgl-sysinfo.lua $(1)/usr/lib/lua/luci/controller/


	$(INSTALL_DIR) $(1)/usr/lib/lua/luci/model/cbi/lvgl-sysinfo
	$(CP) ./luasrc/model/cbi/lvgl-sysinfo/settings.lua $(1)/usr/lib/lua/luci/model/cbi/lvgl-sysinfo/


	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_CONF) ./root/etc/config/lvgl-sysinfo $(1)/etc/config/lvgl-sysinfo

endef

define Package/luci-app-lvgl-sysinfo/postinst
#!/bin/sh
[ -n "$${IPKG_INSTROOT}" ] || { 
    /etc/init.d/h29k-sysinfo enable   # 设置开机启动
    /etc/init.d/h29k-sysinfo start    # 安装后立即启动
}
exit 0
endef

$(eval $(call BuildPackage,$(PKG_NAME)))