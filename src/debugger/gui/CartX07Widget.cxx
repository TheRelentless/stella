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

#include "CartX07.hxx"
#include "PopUpWidget.hxx"
#include "CartX07Widget.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CartridgeX07Widget::CartridgeX07Widget(
      GuiObject* boss, const GUI::Font& lfont, const GUI::Font& nfont,
      int x, int y, int w, int h, CartridgeX07& cart)
  : CartDebugWidget(boss, lfont, nfont, x, y, w, h),
    myCart(cart)
{
  uInt32 size = 16 * 4096;

  ostringstream info;
  info << "64K X07 cartridge, 16 4K banks\n"
       << "Startup bank = " << cart.myStartBank << "\n"
       << "Multiple hotspots, all below $1000\n"
       << "See documentation for further details\n";

  // Eventually, we should query this from the debugger/disassembler
  for(uInt32 i = 0, offset = 0xFFC; i < 16; ++i, offset += 0x1000)
  {
    uInt16 start = (cart.myImage[offset+1] << 8) | cart.myImage[offset];
    start -= start % 0x1000;
    info << "Bank " << std::dec << i << " @ $" << Common::Base::HEX4 << start
         << " - " << "$" << (start + 0xFFF) << "\n";
  }

  int xpos = 10,
      ypos = addBaseInformation(size, "AtariAge / John Payson / Fred Quimby",
                                info.str()) + myLineHeight;

  VariantList items;
  VarList::push_back(items, "  0");
  VarList::push_back(items, "  1");
  VarList::push_back(items, "  2");
  VarList::push_back(items, "  3");
  VarList::push_back(items, "  4");
  VarList::push_back(items, "  5");
  VarList::push_back(items, "  6");
  VarList::push_back(items, "  7");
  VarList::push_back(items, "  8");
  VarList::push_back(items, "  9");
  VarList::push_back(items, " 10");
  VarList::push_back(items, " 11");
  VarList::push_back(items, " 12");
  VarList::push_back(items, " 13");
  VarList::push_back(items, " 14");
  VarList::push_back(items, " 15");
  myBank =
    new PopUpWidget(boss, _font, xpos, ypos-2, _font.getStringWidth(" 15 "),
                    myLineHeight, items, "Set bank ",
                    _font.getStringWidth("Set bank "), kBankChanged);
  myBank->setTarget(this);
  addFocusWidget(myBank);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeX07Widget::loadConfig()
{
  Debugger& dbg = instance().debugger();
  CartDebug& cart = dbg.cartDebug();
  const CartState& state = static_cast<const CartState&>(cart.getState());
  const CartState& oldstate = static_cast<const CartState&>(cart.getOldState());

  myBank->setSelectedIndex(myCart.getBank(), state.bank != oldstate.bank);

  CartDebugWidget::loadConfig();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void CartridgeX07Widget::handleCommand(CommandSender* sender,
                                      int cmd, int data, int id)
{
  if(cmd == kBankChanged)
  {
    myCart.unlockBank();
    myCart.bank(myBank->getSelected());
    myCart.lockBank();
    invalidate();
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
string CartridgeX07Widget::bankState()
{
  ostringstream& buf = buffer();

  buf << "Bank = " << std::dec << myCart.myCurrentBank;

  return buf.str();
}
