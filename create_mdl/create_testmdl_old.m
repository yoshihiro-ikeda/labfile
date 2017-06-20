function create_testmdl(filename,blknum)

if exist(filename) == 4
    close_system(filename,0);
    delete_filename = sprintf('%s.slx',filename);
    delete(delete_filename);
end;

stage_blknum = [1 1 1 1 1 1 1 2 2 3];

sysH_ss = load_system('ss_blks_lib');
sysH_mm = load_system('mm_blks_lib');

ss_blk_list = find_system(sysH_ss,'FindAll','On','type','Block');
ss_blk_list_size = size(ss_blk_list);

disp(ss_blk_list);

mm_blk_list = find_system(sysH_mm,'FindAll','On','type','Block');
mm_blk_list_size = size(mm_blk_list);

load_system('root');
sys = save_system('root',filename);
load_system(sys);

srcBH = get_param('test/In1','Handle');
srcPH = get_param(srcBH,'PortHandles');


for i = 1:3
    add_blk_randid = randi([1,4],1,1);
    add_blk_name = sprintf('%s/%s%d',filename,get_param(ss_blk_list(add_blk_randid),'name'),i);
    add_BH = add_block(ss_blk_list(add_blk_randid),add_blk_name);
    dst_PH = get_param(add_BH,'PortHandles');
    add_line(filename,srcPH.Outport,dst_PH.Inport);
    srcPH = dst_PH;
end;
%kokomade bunkinashi

inport_list = [];
outport_list = dst_PH.Outport;

disp(outport_list);


for i = 4:blknum
    next_outport_list = [];
    for j = 1:stage_blknum(randi([1,10],1,1))
        add_blk_randid = randi([1,7],1,1);
        add_blk_name = sprintf('%s/%s%d_%d',filename,get_param(mm_blk_list(add_blk_randid),'name'),i,j);
        %i = i + 1;
        add_BH = add_block(mm_blk_list(add_blk_randid),add_blk_name);
        dst_PH = get_param(add_BH,'PortHandles');
        for k = 1:size(dst_PH.Inport,2)
            inport_list = [inport_list dst_PH.Inport(k)];
        end;
        for k = 1:size(dst_PH.Outport,2)
            next_outport_list = [next_outport_list dst_PH.Outport(k)];
        end;
    end;
    disp(j);
    %入力数と出力数が同じ場合
    if size(inport_list) == size(outport_list)
        deal = randperm(size(inport_list,2));
        for k = 1:size(inport_list,2)
            add_line(filename,outport_list(k),inport_list(deal(k)));
        end;
        tmp_outport_list = [];
    %入力数＞出力数
    %一部の出力を分岐させる
    elseif size(inport_list,2) > size(outport_list,2)
        deal = randperm(size(outport_list,2));
        for k = 1:size(outport_list,2)
            add_line(filename,outport_list(deal(k)),inport_list(k));
        end;
        %deal = randperm(size(inport_list,2) - size(outport_list,2));
        %deal = randperm(size(inport_list,2));
        disp('deal');
        disp(deal);
        for k = size(outport_list,2) + 1:size(inport_list,2)
%             disp('k');
%             disp(k);
%             disp('size');
%             disp(size(outport_list,2)+1);
%             disp(deal(rem(k,size(outport_list,2)) + 1));
            add_line(filename,outport_list(deal(rem(k,size(outport_list,2)) + 1)),inport_list(k));
            %add_line(filename,outport_list(deal(randi([1,size(outport_list,2)],1,1))),inport_list(k));
        end;
        tmp_outport_list = [];    
    %入力数＜出力数
    %次回以降のoutport_listに引き継ぎ
    else
        deal = randperm(size(outport_list,2));
        for k = 1:size(inport_list,2)
            add_line(filename,outport_list(deal(k)),inport_list(k));
        end;
        %outport_listから選択されたportを排除
        tmp_outport_list = outport_list(1);
        for k = size(inport_list,2) + 1:size(outport_list,2)
            tmp_outport_list = [tmp_outport_list outport_list(k)];
        end;
        %outport_list = tmp_outport_list;
    end;
    %inport_listを空にして次のステージを構成
    inport_list = [];
    outport_list = [tmp_outport_list next_outport_list];
end;

if size(outport_list,2) > 0
    for i = 1:size(outport_list,2)
        add_blk_name = sprintf('%s/Out%d',filename,i);
        add_blkH = add_block('simulink/Sinks/Out',add_blk_name);
        add_pH = get_param(add_blkH,'PortHandles');
    end;
end;
%disp(inport_list);

open_system(sys);

end
