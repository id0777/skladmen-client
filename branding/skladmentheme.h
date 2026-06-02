/*
 * SkladMen Desktop Client — branding theme.
 *
 * This header is #include'd directly into src/libsync/theme.cpp (via the
 * THEME_INCLUDE CMake variable set in OEM.cmake), and SkladMenTheme is
 * instantiated there as `new THEME_CLASS`. It is therefore header-only: all
 * overrides are inline so no separate translation unit needs to be compiled or
 * linked, and the class deliberately omits Q_OBJECT (it adds no new signals or
 * slots, so the QObject meta-object of the base class is sufficient).
 *
 * Derives from ownCloudTheme to keep its sensible wizard/button defaults and
 * overrides only what SkladMen needs to change.
 *
 * Based on owncloud/client (GPLv2-or-later). This file is part of the SkladMen
 * fork; corresponding source is published with the distributed binaries.
 */

#ifndef SKLADMEN_THEME_H
#define SKLADMEN_THEME_H

#include "owncloudtheme.h"

namespace OCC {

class SkladMenTheme : public ownCloudTheme
{
public:
    SkladMenTheme() = default;

    /**
     * Pre-fill (but do NOT lock) the server address field of the connection
     * wizard with our apex domain. Unlike overrideServerUrl(), which hides the
     * field, this leaves it editable so SaaS tenants can point the same
     * installer at their own *.skladmen.ru subdomain.
     */
    QString defaultServerUrl() const override
    {
        return QStringLiteral("https://skladmen.ru");
    }

    // Brand accent (SkladMen blue, #1f6feb) for the setup-wizard header.
    QColor wizardHeaderBackgroundColor() const override
    {
        return QColor(0x1f, 0x6f, 0xeb);
    }

    QColor wizardHeaderTitleColor() const override
    {
        return Qt::white;
    }

    // Primary action buttons in the brand colour.
    QmlButtonColor primaryButtonColor() const override
    {
        const QColor button(0x1f, 0x6f, 0xeb);
        return { button, Qt::white, button.darker() };
    }

    /**
     * The custom-theme resource bundle does not ship the upstream
     * "oc-image-about" asset, so reuse the wizard logo for the About dialog
     * instead of returning a null icon.
     */
    QIcon aboutIcon() const override
    {
        return wizardHeaderLogo();
    }
};

}

#endif // SKLADMEN_THEME_H
