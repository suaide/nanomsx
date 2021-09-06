Procedure WriteVram (VramBlockUsed:Byte; VramAddr, RamAddr, ByteCount: Integer);

{ VramBlockUsed  = 0 = first 64 Kb
                  1 = second 64 Kb
                  2 = Expansion Vram 64 Kb }

Var Expansion, AddrHi, AddrMid, AddrLo :Byte;

Begin
    If VramBlockUsed = 2 Then
        Expansion := $40 {Set the bit 6 (MXC) }
    Else
        Expansion := 0 ; {No expansion vram used}
    AddrHi := Hi(VramAddr) Div $40;
    If VramBlockUsed = 1 Then
        AddrHi := AddrHi + 4;   {Set addr bit 16 in reg 14 = bit 2 }
    AddrLo := Lo(VramAddr);
    AddrMid := Hi(Vramaddr) And 63 ;
    Inline(
            $F3/$3A/ Expansion /$D3/$99/$3E/$2D/$F6/$80/$D3/$99/$3A/ AddrHi /$D3/
            );