# SkladMen branding overlay for the ownCloud Desktop client.
#
# This file is auto-detected by THEME.cmake because it lives in the top-level
# `branding/` directory of the fork. It overrides the vanilla ownCloud branding
# variables (see ../OWNCLOUD.cmake for the full list of defaults).
#
# Upstream sources are intentionally left untouched except for one tiny,
# clearly-marked patch (Theme::defaultServerUrl, see ../src/libsync/theme.{h,cpp}
# and ../src/gui/newwizard/states/serverurlsetupwizardstate.cpp) so that security
# updates from upstream rebase cleanly.

set( APPLICATION_NAME       "SkladMen" )
set( APPLICATION_SHORTNAME  "SkladMen" )
set( APPLICATION_EXECUTABLE "skladmen" )
set( APPLICATION_DOMAIN     "skladmen.ru" )
set( APPLICATION_VENDOR     "SkladMen" )
set( APPLICATION_UPDATE_URL "https://skladmen.ru/client/" CACHE STRING "URL for updater" )
set( APPLICATION_ICON_NAME  "skladmen" )
set( APPLICATION_VIRTUALFILE_SUFFIX "skladmen" CACHE STRING "Virtual file suffix (not including the .)")

set( LINUX_PACKAGE_SHORTNAME "skladmen" )

# Header-only theme subclass (see skladmentheme.h). THEME_INCLUDE is #include'd
# directly into src/libsync/theme.cpp, and THEME_CLASS is instantiated there.
set( THEME_CLASS            "SkladMenTheme" )
set( THEME_INCLUDE          "${OEM_THEME_DIR}/skladmentheme.h" )

set( APPLICATION_REV_DOMAIN "ru.skladmen.desktopclient" )

# Reuse the upstream NSIS installer wizard bitmaps for now (cosmetic — can be
# rebranded later by pointing this at our own .bmp set).
set( WIN_SETUP_BITMAP_PATH  "${CMAKE_SOURCE_DIR}/admin/win/nsi" )

# We ship our own builds; crash reporter stays off (vanilla default).
option( WITH_CRASHREPORTER "Build crashreporter" OFF )
