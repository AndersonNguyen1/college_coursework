onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /tb_top/reset
add wave -noupdate /tb_top/tb_clk
add wave -noupdate /tb_top/riscV/dp/instr_mem/rd
add wave -noupdate /tb_top/riscV/dp/D.Curr_Instr
add wave -noupdate /tb_top/tb_WB_Data
add wave -noupdate /tb_top/riscV/dp/D.rd
add wave -noupdate /tb_top/riscV/dp/D.RegWrite
add wave -noupdate /tb_top/riscV/dp/ALUResult
add wave -noupdate -radix binary /tb_top/riscV/ac/Operation
add wave -noupdate -radix binary /tb_top/riscV/ac/ALUOp
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {1655881 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 172
configure wave -valuecolwidth 38
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {1595052 ps} {1796176 ps}
