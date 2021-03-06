//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2018 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef OPTIONS_DIALOG_HXX
#define OPTIONS_DIALOG_HXX

class CommandSender;
class DialogContainer;
class GuiObject;
class OSystem;
class VideoDialog;
class AudioDialog;
class InputDialog;
class UIDialog;
class SnapshotDialog;
class ConfigPathDialog;
class RomAuditDialog;
class GameInfoDialog;
#ifdef CHEATCODE_SUPPORT
  class CheatCodeDialog;
#endif
class HelpDialog;
class AboutDialog;
class LoggerDialog;

#include "Dialog.hxx"
#include "bspf.hxx"

class DeveloperDialog;

class OptionsDialog : public Dialog
{
  public:
    // Current Stella mode
    enum stellaMode
    {
      launcher,
      emulator,
      debugger
    };

    OptionsDialog(OSystem& osystem, DialogContainer& parent, GuiObject* boss,
                  int max_w, int max_h, stellaMode mode);
    virtual ~OptionsDialog();

  private:
    void loadConfig() override;
    void handleCommand(CommandSender* sender, int cmd, int data, int id) override;

  private:
    unique_ptr<VideoDialog>      myVideoDialog;
    unique_ptr<AudioDialog>      myAudioDialog;
    unique_ptr<InputDialog>      myInputDialog;
    unique_ptr<UIDialog>         myUIDialog;
    unique_ptr<SnapshotDialog>   mySnapshotDialog;
    unique_ptr<ConfigPathDialog> myConfigPathDialog;
    unique_ptr<RomAuditDialog>   myRomAuditDialog;
    unique_ptr<GameInfoDialog>   myGameInfoDialog;
  #ifdef CHEATCODE_SUPPORT
    unique_ptr<CheatCodeDialog>  myCheatCodeDialog;
  #endif
    unique_ptr<LoggerDialog>     myLoggerDialog;
    unique_ptr<DeveloperDialog>  myDeveloperDialog;
    unique_ptr<HelpDialog>       myHelpDialog;
    unique_ptr<AboutDialog>      myAboutDialog;

    ButtonWidget* myRomAuditButton;
    ButtonWidget* myGameInfoButton;
    ButtonWidget* myCheatCodeButton;

    // Indicates if this dialog is used for global (vs. in-game) settings
    stellaMode myMode;

    GuiObject* _boss;

    enum {
      kVidCmd      = 'VIDO',
      kAudCmd      = 'AUDO',
      kInptCmd     = 'INPT',
      kUsrIfaceCmd = 'URIF',
      kSnapCmd     = 'SNAP',
      kCfgPathsCmd = 'CFGP',
      kAuditCmd    = 'RAUD',
      kInfoCmd     = 'INFO',
      kCheatCmd    = 'CHET',
      kLoggerCmd   = 'LOGG',
      kDevelopCmd  = 'DEVL',
      kHelpCmd     = 'HELP',
      kAboutCmd    = 'ABOU',
      kExitCmd     = 'EXIM'
    };

  private:
    // Following constructors and assignment operators not supported
    OptionsDialog() = delete;
    OptionsDialog(const OptionsDialog&) = delete;
    OptionsDialog(OptionsDialog&&) = delete;
    OptionsDialog& operator=(const OptionsDialog&) = delete;
    OptionsDialog& operator=(OptionsDialog&&) = delete;
};

#endif
