ren Song.c output_bank2.c
mod2gbt .\mods\template.mod songb -c 1
ren output.c output_bank1.c
lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o testSoundMusic.o testSoundMusic.c

lcc -Wf-bo2 -c -o output_bank2.o output_bank2.c

lcc -Wf-bo1 -c -o output_bank1.o output_bank1.c

lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o gbt_player.o gbt_player.s

lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o gbt_player_bank1.o gbt_player_bank1.s



lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-yt1 -Wl-yo4 -Wl-ya0 -o SoundMusic-simpleBankingMBC1-20141208.gb testSoundMusic.o output_bank2.o output_bank1.o gbt_player.o gbt_player_bank1.o



del *.o *.lst *.map *.sym



pause