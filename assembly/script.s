.thumb
.align 2


.include "../xse_commands.s"
.include "../xse_defines.s"
  
.global Script_SaveGame

Script_SaveGame:
  pause 0x4
  special 0x5D
  waitkeypress
  end
