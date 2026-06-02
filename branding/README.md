# SkladMen branding overlay

This directory rebrands the ownCloud Desktop client as **SkladMen**. It is
auto-detected by the top-level `THEME.cmake` (because a `branding/` directory
exists), which then includes [`OEM.cmake`](OEM.cmake) and builds the theme
resource bundle from `theme/`.

## What it changes

| Area | How |
|------|-----|
| App name / executable / vendor / domain | [`OEM.cmake`](OEM.cmake) (`APPLICATION_*`) → `SkladMen`, `skladmen.exe`, `skladmen.ru` |
| Reverse-DNS id, VFS suffix | `ru.skladmen.desktopclient`, `.skladmen` |
| Auto-update feed | `APPLICATION_UPDATE_URL = https://skladmen.ru/client/` (appcast not yet published) |
| App / tray / sidebar icons | `theme/colored/*-skladmen-icon.png`, `*-skladmen-sidebar.png` (16–1024), `*.svg` |
| Wizard logo, status icons | `theme/{colored,universal}/wizard_logo.svg`, `theme/{colored,dark,black,white}/state-*.svg` |
| Brand colour (#1f6feb), default server URL | [`skladmentheme.h`](skladmentheme.h) (`SkladMenTheme : ownCloudTheme`) |

`skladmentheme.h` is **header-only** and `#include`d straight into
`src/libsync/theme.cpp` via the `THEME_INCLUDE` CMake variable; `THEME_CLASS`
(`SkladMenTheme`) is instantiated there. It deliberately has no `Q_OBJECT`
(no new signals/slots), so it needs no separate compilation or moc pass.

## Upstream patch (kept minimal on purpose)

Everything above is pure overlay **except** one small, clearly-marked change so
that upstream security updates rebase cleanly:

- `src/libsync/theme.{h,cpp}` — adds `virtual QString Theme::defaultServerUrl()`
  (empty by default = vanilla behaviour).
- `src/gui/newwizard/states/serverurlsetupwizardstate.cpp` — pre-fills that URL
  into the connection wizard **while keeping the field editable**.

This is intentionally *not* `Theme::overrideServerUrl()`, which would hide and
lock the field — SaaS tenants must be able to point the same installer at their
own `*.skladmen.ru` subdomain.

## Building (Windows installer)

Builds run on GitHub Actions via KDE Craft (`.github/workflows/main.yml`,
unchanged — the `branding/` dir is auto-detected). The Windows job produces an
**NSIS `.exe` installer** (upstream does not ship an MSI) as a build artifact.
Trigger it with "Run workflow" (workflow_dispatch) or a pull request.

## Pulling upstream updates

```sh
git fetch upstream --tags
git rebase v<new-tag>      # only the 3 source-file hunks above can conflict
```

## Licensing

The client is GPLv2-or-later. The corresponding source — this fork including
this overlay — is published alongside every distributed binary, satisfying the
GPL's source-availability requirement.

## Regenerating the PNG icon set from the SVG

```sh
for s in 16 22 24 32 48 64 128 256 512 1024; do
  rsvg-convert -w $s -h $s theme/colored/skladmen-icon.svg -o theme/colored/${s}-skladmen-icon.png
  cp theme/colored/${s}-skladmen-icon.png theme/colored/${s}-skladmen-sidebar.png
done
```
