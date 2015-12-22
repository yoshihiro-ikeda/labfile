function add_outport(sys)

load_system(sys);
blk_list = find_system(sys,'Type','Block');
disp(blk_list);
blk_num = size(blk_list);
count_out = 0;

for i = 1:blk_num
    target_blk = blk_list(i);
    if strcmp(get_param(target_blk,'Blocktype'),'UnitDelay')
        count_out = count_out + 1;
        Dstblockname = sprintf('%s/Out%d',sys,count_out);
        new_block = add_block('simulink/Ports & Subsystems/Out1',Dstblockname,'MakeNameUnique','On');
        UD_position = get_param(char(target_blk),'position');
        Out_position = UD_position;
        Out_position(1) = Out_position(1) + 100;
        Out_position(2) = Out_position(2) + 10;
        Out_position(3) = Out_position(3) + 100;
        Out_position(4) = Out_position(4) - 10;
        set_param(new_block,'position',Out_position);
        Srcportnum = sprintf('%s/%d',get_param(char(target_blk),'Name'),1);
        Dstportnum = sprintf('%s/%d',get_param(new_block,'Name'),1);
        add_line(sys,Srcportnum,Dstportnum);
    end
end
        
save_system(sys);