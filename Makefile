#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

export TARGET := $(shell basename $(CURDIR))
export TOPDIR := $(CURDIR)

# GMAE_ICON is the image used to create the game icon, leave blank to use default rule
GAME_ICON :=

# specify a directory which contains the nitro filesystem
# this is relative to the Makefile
NITRO_FILES :=

# These set the information text in the nds file
GAME_TITLE     := acekard
GAME_SUBTITLE1 := Real Play Gear
GAME_SUBTITLE2 := www.acekard.com

include $(DEVKITARM)/ds_rules

.PHONY: checkarm7 checkarm9 checkarm9_ak2 checkarm9_dsi clean

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
all:	checkarm7 checkarm9 checkarm9_ak2 checkarm9_dsi \
		$(TARGET).nds $(TARGET)_ak2.nds $(TARGET).dsi
	@$(MAKE) organize_files

#---------------------------------------------------------------------------------
checkarm7:
	$(MAKE) -C arm7

#---------------------------------------------------------------------------------
checkarm9:
	$(MAKE) -C arm9

#---------------------------------------------------------------------------------
checkarm9_ak2:
	$(MAKE) -C arm9_ak2

#---------------------------------------------------------------------------------
checkarm9_dsi:
	$(MAKE) -C arm9_dsi

#---------------------------------------------------------------------------------
$(TARGET).nds : $(NITRO_FILES) arm7/$(TARGET).elf arm9/$(TARGET).elf
	ndstool	-c $(TARGET).nds -7 arm7/$(TARGET).elf -9 arm9/$(TARGET).elf \
	-b $(GAME_ICON) "$(GAME_TITLE);$(GAME_SUBTITLE1);$(GAME_SUBTITLE2)" \
	-h 0x200 \
	$(_ADDFILES)

#---------------------------------------------------------------------------------
$(TARGET)_ak2.nds : $(NITRO_FILES) arm7/$(TARGET).elf arm9_ak2/$(TARGET).elf
	ndstool	-c $@ -7 arm7/$(TARGET).elf -9 arm9_ak2/$(TARGET).elf \
	-b $(GAME_ICON) "$(GAME_TITLE);$(GAME_SUBTITLE1);$(GAME_SUBTITLE2)" \
	$(_ADDFILES)
	dlditool DLDI/ak2_sd.dldi $@

#---------------------------------------------------------------------------------
$(TARGET).dsi : $(NITRO_FILES) arm7/$(TARGET).elf arm9_dsi/$(TARGET).elf
	ndstool	-c $@ -7 arm7/$(TARGET).elf -9 arm9_dsi/$(TARGET).elf \
	-b $(GAME_ICON) "$(GAME_TITLE);$(GAME_SUBTITLE1);$(GAME_SUBTITLE2)" \
	-g NEXT 01 "AKMENU" -z 80040407 -u 00030004 -a 00000138 -p 0001 \
	$(_ADDFILES)

#---------------------------------------------------------------------------------
arm7/$(TARGET).elf:
	$(MAKE) -C arm7

#---------------------------------------------------------------------------------
arm9/$(TARGET).elf:
	$(MAKE) -C arm9

#---------------------------------------------------------------------------------
arm9_ak2/$(TARGET).elf:
	$(MAKE) -C arm9_ak2

#---------------------------------------------------------------------------------
arm9_dsi/$(TARGET).elf:
	$(MAKE) -C arm9_dsi

#---------------------------------------------------------------------------------
organize_files:
	@mkdir -p build
	@mv -f $(TARGET).nds $(TARGET).dsi build/
	@cd build && \
	cp $(TARGET).nds launcher_$(TARGET).nds && \
	cp $(TARGET).dsi launcher_$(TARGET).dsi

#---------------------------------------------------------------------------------
clean:
	$(MAKE) -C arm9 clean
	$(MAKE) -C arm9_ak2 clean
	$(MAKE) -C arm9_dsi clean
	$(MAKE) -C arm7 clean
	rm -rf data build
	rm -f *.nds *.dsi
