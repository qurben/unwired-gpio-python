include $(TOPDIR)/rules.mk

PKG_NAME:=unwired-gpio-python
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

define Package/unwired-gpio-python
	SECTION:=utils
	CATEGORY:=Languages/Python
	TITLE:=Unwired GPIO example
endef

define Package/unwired-gpio-python/description
 GPIO bindings for Python for the Unwired One
endef

MAKE_OPTS:= \
	ARCH="$(LINUX_KARCH)" \
	CROSS_COMPILE="$(TARGET_CROSS)" \
	SUBDIRS="$(PKG_BUILD_DIR)"

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Build/Compile
	make -C $(PKG_BUILD_DIR) \
	        $(TARGET_CONFIGURE_OPTS) \
	        CFLAGS="$(TARGET_CFLAGS) $(TARGET_CPPFLAGS)" \
	        LIBS="$(TARGET_LDFLAGS)"
endef

define Package/unwired-gpio-python/install
	$(INSTALL_DIR) $(1)/usr/lib/python2.7/unwired
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/__init__.py $(1)/usr/lib/python2.7/unwired/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/gpio.so $(1)/usr/lib/python2.7/unwired/
endef

$(eval $(call BuildPackage,unwired-gpio-python))