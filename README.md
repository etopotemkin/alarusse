# Felucca RAVE (fork)

A fork of Felucca for the M-VAVE FM-1 aimed at rave / hard-techno live sets. Upstream: [hugelton/Felucca](https://github.com/hugelton/Felucca). Not affiliated with M-VAVE or Hügelton.

**Added so far**
- **RUMBLE kick** — DRUM > KICK has a third choice next to PUNCH and ROUND: the punchy kick followed by a low tail that swells in as the kick's body dies (sidechain built in), roughened by low noise, driven and low-passed. On the DRUM track: TONE = the tail's low-pass (60–300 Hz), DECY = its length, SNAP = its grit.
- **RAVE KIT** preset (DRUM): STD kit with the RUMBLE kick.
- **Russian folk instruments**: PHYS BALALAIKA (open strings ringing a fourth up; tremolo with RATCH), DOMRA, GUSLI, KOLOKOL (church bell), ZVON (small bells); ANALOG BAYAN, GARMON (the wide "razliv" detune); VOICE ZHALEIKA (hornpipe), KHOR (folk choir); and KONTRABAS (contrabass balalaika), LIRA (hurdy-gurdy), GUDOK (bowed fiddle), DUDA (bagpipe), KUGIKLY (panpipes), SVIREL (whistle), TALYANKA (small accordion), VARGAN (jaw harp), ROZHOK (Vladimir horn).
- **FOLK kit** (DRUM > KIT FOLK, preset FOLK KIT): RUMBLE kick, BUBEN (tambourine), TRESHCHOTKA (rattle), LOZHKI (spoons), BUBENTSY (sleigh bells), a frame drum, KOROBOCHKA (wood box), KOLOKOLCHIK (hand bell).
- **Folk phrases** (SAVE > PHRASES): KOROBEIN, BARYNYA, OOMPAH (the bayan's left hand), FOLKBEAT (for the FOLK kit); the folk presets suggest them.
- **Power-on band**: ANALOG BAYAN, PHYS BALALAIKA, VOICE ZHALEIKA, DRUM FOLK KIT (`FELUCCA_FOLK_DEF=0`: upstream's sounds; the host tests use those).
- **FX layer: BUILD UP and DROP** on F5 / G5 (free upstream). BUILD UP: hold it for a two-bar riser (opening noise, the mix's high-pass rising), let go for the drop. DROP: every track muted while held, the reverb and delay ring on; let go and the band is back on the next beat.
- **Folk UI themes** (MENU > COLOR): HOHLOMA (black lacquer, gold, cinnabar), GZHEL (porcelain and cobalt), PALEKH (black lacquer, ultramarine, gold), ZHOSTOV (Zhostovo: black, roses, leaves), GORODEC (Gorodets: ochre wood, madder red, cobalt), DYMKA (Dymkovo: white clay, crimson, green). The FOLK kit's lanes are named on the grid (BD BB TR LZ BC TM KB ZV).
- **Theme screen at the first power-on** (and once after updating to this firmware): any knob steps through the 16 themes with a live preview, a button keeps it.
- `tests/folk_demo.c`: an 8-bar folk-rave demo through the real engines.
- Felucca-Engines is vendored in `firmware/engines/` (MIT) instead of a submodule, so the fork's presets build in CI.

**Planned**: show sync over USB MIDI (Resolume, lighting).

Builds run on GitHub Actions (`.github/workflows/build-fwsc.yml`): the installable `.fwsc` is attached to each run as an artifact.

---

# Felucca

[![License: GPL-3.0-only](https://img.shields.io/badge/license-GPL--3.0--only-blue.svg)](LICENSE)

Felucca is open-source custom synthesizer firmware for the **M-VAVE FM-1**.

The FM-1 is the only supported hardware target. This project does not provide, maintain, or accept requests for ports to other devices or software platforms.

## Install

**Stable release: 1.8.1.** Connect your FM-1 by USB and use the [web installer](https://hugelton.github.io/Felucca/) in Chrome or Edge. The installer offers a way back to the official V15 firmware. Back up your projects and presets before changing firmware.

**Newer FM-1 flash: 1.8.2 beta.** Some newer FM-1 units use UC25HQ80 flash (JEDEC ID `0xB36014`). [1.8.2-beta](https://github.com/hugelton/Felucca/releases/tag/v1.8.2-beta) adds recognition for that chip; testing on the revised hardware is still pending. See [issue #320](https://github.com/hugelton/Felucca/issues/320). It is not the stable release.

## Project resources

- [Web installer](https://hugelton.github.io/Felucca/)
- [Web editor](https://hugelton.github.io/Felucca/webapp/editor/) ([source](https://github.com/hugelton/Felucca-WebApp))
- [Manual and release notes](https://github.com/hugelton/Felucca/wiki/Home)
- [Building from source](BUILDING.md)
- [Issue tracker](https://github.com/hugelton/Felucca/issues)

The firmware uses [Felucca-Engines](https://github.com/hugelton/Felucca-Engines) (MIT) for its built-in sound engines and [felucca-bsp](https://github.com/hugelton/felucca-bsp) (MPL-2.0) for the FM-1 hardware layer. Neither repository implies support for Felucca on other hardware.

## Development and support

Felucca focuses on the FM-1. Third-party modifications and ports are independent projects and are not tested or supported here. Contributions are considered at the maintainer's discretion; no development schedule or ongoing support is promised.

Felucca is developed with the assistance of AI coding agents (code, tests, documentation, translation, maintenance). Design, features, sounds and direction are the maintainer's or the community's; no generative AI is used for music, icons or artwork. See [On AI-Assisted Development and Responsibility](https://github.com/hugelton/Felucca/discussions/166).

## Credits and licence

Felucca is free software under [GPL-3.0-only](LICENSE); the Hügelton Sample Pack is CC0 1.0. The engines and hardware layer retain their own licences. See [CREDITS.md](CREDITS.md) and [LICENSING.md](LICENSING.md).

M-VAVE and FM-1 are trademarks of their respective owners. Felucca is not affiliated with, endorsed by or supported by M-VAVE.

Copyright (C) 2026 Leo Kuroshita (@kurogedelic), Hügelton Instruments
