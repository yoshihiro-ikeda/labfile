function add_inport(sys)

load_system(sys);
blk_list = find_system(sys,'Type','Block');
disp(blk_list);
blk_num = size(blk_list);
line_list = find_system(sys,'FindAll','On','type','line');
line_num = size(line_list);

for i = 1:line_num(1)
    blk_list = find_system(sys,'Type','Block');
    blkH_line_in = get_param(line_list(i),'SrcBlockHandle');
    if blkH_line_in == -1
        target_blk = get_param(get_param(line_list(i),'DstBlockHandle'),'Name');
        for j = 1:blk_num
            if(strcmp(get_param(blk_list(j),'blockType'),'Inport'))
                break
            end
        end
        coodinates = get_param(line_list(i),'Points');
        coodinates_right = coodinates(2,1);
        coodinates_middle = coodinates(1,2);
        name = char(blk_list(j));
        new_block = add_block(name,name,'MakeNameUnique','On');
        pre_coodinates = get_param(name,'position');
        dif_elev = (pre_coodinates(4) - pre_coodinates(2))/2;
        dif_crs = pre_coodinates(3) - pre_coodinates(1);
        line_crs = coodinates(2,1) - coodinates(1,1);
        coodinates = [coodinates_right-dif_crs-line_crs,coodinates_middle-dif_elev,coodinates_right-line_crs,coodinates_middle+dif_elev];
        set_param(new_block,'position',coodinates);
        pH = get_param(line_list(i),'DstPortHandle');
        pNum = get_param(pH,'PortNumber');
        delete_line(line_list(i));
        Dstportname = sprintf('%s/%d',target_blk,pNum);
        Srcportname = sprintf('%s/1',get_param(new_block,'Name'));
        add_line(sys,Srcportname,Dstportname);
    end
end

save_system(sys);