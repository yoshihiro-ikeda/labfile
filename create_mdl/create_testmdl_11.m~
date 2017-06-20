function create_testmdl_11(filename,blknum)

if exist(filename) == 4
    close_system(filename,0);
    delete_filename = sprintf('%s.slx',filename);
    delete(delete_filename);
end;

stage_blknum = [1 1 1 1 1 1 1 2 2 3];

sysH_ss = load_system('ss_blks_lib');
sysH_mm = load_system('mm_blks_lib');
sysH_ll = load_system('ll_blks_lib');

ss_blk_list = find_system(sysH_ss,'FindAll','On','type','Block');
ss_blk_list_size = size(ss_blk_list);

disp(ss_blk_list);

mm_blk_list = find_system(sysH_mm,'FindAll','On','type','Block');
mm_blk_list_size = size(mm_blk_list);

ll_blk_list = find_system(sysH_ll,'FindAll','On','type','Block');
ll_blk_list_size = size(ll_blk_list);

load_system('root');
sys = save_system('root',filename);
load_system(sys);


tmpname = sprintf('%s/In1',filename);
srcBH = get_param(tmpname,'Handle');
srcPH = get_param(srcBH,'PortHandles');

position = [0 0 0 0];

for i = 1:3
    add_blk_randid = randi([1,4],1,1);
    add_blk_name = sprintf('%s/%s%d',filename,get_param(ss_blk_list(add_blk_randid),'name'),i);
    add_BH = add_block(ss_blk_list(add_blk_randid),add_blk_name);
    dst_PH = get_param(add_BH,'PortHandles');
    add_line(filename,srcPH.Outport,dst_PH.Inport,'autorouting','on');
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
        add_blk_name = sprintf('%s/%s%d%d',filename,get_param(mm_blk_list(add_blk_randid),'name'),i,j);
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
            add_line(filename,outport_list(k),inport_list(deal(k)),'autorouting','on');
        end;
        tmp_outport_list = [];
    %入力数＞出力数
    %一部の出力を分岐させる
    elseif size(inport_list,2) > size(outport_list,2)
        deal = randperm(size(outport_list,2));
        for k = 1:size(outport_list,2)
            add_line(filename,outport_list(deal(k)),inport_list(k),'autorouting','on');
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
            add_line(filename,outport_list(deal(rem(k,size(outport_list,2)) + 1)),inport_list(k),'autorouting','on');
            %add_line(filename,outport_list(deal(randi([1,size(outport_list,2)],1,1))),inport_list(k));
        end;
        tmp_outport_list = [];    
    %入力数＜出力数
    %次回以降のoutport_listに引き継ぎ
    else
        deal = randperm(size(outport_list,2));
        for k = 1:size(inport_list,2)
            add_line(filename,outport_list(deal(k)),inport_list(k),'autorouting','on');
        end;
        %outport_listから選択されたportを排除
        tmp_outport_list = outport_list(1);
        for k = size(inport_list,2) + 1:size(outport_list,2)
            tmp_outport_list = [tmp_outport_list outport_list(deal(k))];
        end;
        %outport_list = tmp_outport_list;
    end;
    %inport_listを空にして次のステージを構成
    inport_list = [];
    outport_list = [tmp_outport_list next_outport_list];
end;

last_id = 0;
while size(outport_list,2) ~= 0
    disp('last_id')
    disp(size(outport_list,2));
    next_outport_list = [];
    if size(outport_list,2) == 1
        for i = 1:size(outport_list,2)
            add_blk_name = sprintf('%s/Out%d',filename,i+1);
            add_blkH = add_block('simulink/Sinks/Out1',add_blk_name);
            add_pH = get_param(add_blkH,'PortHandles');
            add_line(filename,outport_list(i),add_pH.Inport,'autorouting','on');
            outport_list = [];
        end;
    elseif size(outport_list,2) > 1
        last_id = last_id + 1;
        for j = 1:stage_blknum(randi([1,10],1,1))
            %add_blk_randid = randi([1,3],1,1);
            add_blk_randid = 1;
            add_blk_name = sprintf('%s/%s_last%d%d',filename,get_param(ll_blk_list(add_blk_randid),'name'),last_id,j);
            add_BH = add_block(ll_blk_list(add_blk_randid),add_blk_name);
            dst_PH = get_param(add_BH,'PortHandles');
            for k = 1:size(dst_PH.Inport,2)
                inport_list = [inport_list dst_PH.Inport(k)];
            end;
            for k = 1:size(dst_PH.Outport,2)
                next_outport_list = [next_outport_list dst_PH.Outport(k)];
            end;
        end;
        %入力数と出力数が同じ場合
        if size(inport_list) == size(outport_list)
            deal = randperm(size(inport_list,2));
            for k = 1:size(inport_list,2)
                add_line(filename,outport_list(k),inport_list(deal(k)),'autorouting','on');
            end;
            tmp_outport_list = [];
            %入力数＞出力数
            %一部の出力を分岐させる
        elseif size(inport_list,2) > size(outport_list,2)
            deal = randperm(size(outport_list,2));
            for k = 1:size(outport_list,2)
                add_line(filename,outport_list(deal(k)),inport_list(k),'autorouting','on');
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
                add_line(filename,outport_list(deal(rem(k,size(outport_list,2)) + 1)),inport_list(k),'autorouting','on');
                %add_line(filename,outport_list(deal(randi([1,size(outport_list,2)],1,1))),inport_list(k));
            end;
            tmp_outport_list = [];
            %入力数＜出力数
            %次回以降のoutport_listに引き継ぎ
        else
            deal = randperm(size(outport_list,2));
            for k = 1:size(inport_list,2)
                add_line(filename,outport_list(deal(k)),inport_list(k),'autorouting','on');
            end;
            %outport_listから選択されたportを排除
            tmp_outport_list = outport_list(1);
            for k = size(inport_list,2) + 1:size(outport_list,2)
                tmp_outport_list = [tmp_outport_list outport_list(deal(k))];
            end;
            %outport_list = tmp_outport_list;
        end;
        %inport_listを空にして次のステージを構成
        inport_list = [];
        outport_list = [tmp_outport_list next_outport_list];
    end;
end;
%disp(inport_list);

load_system(sys);
blks = find_system(filename,'FindAll','On','type','Block');

Simulink.BlockDiagram.createSubSystem(blks);

open_system(sys);

set_param(filename,'SolverType','Fixed-step');
set_param(filename,'Solver','FixedStepDiscrete');
set_param(filename,'FixedStep','0.1');
set_param(filename,'BlockReduction','off');
set_param(filename,'OptimizeBlockIOStorage','off');
set_param(filename,'SystemTargetFile','ert.tlc');
set_param(filename,'GenCodeOnly','on');
set_param(filename,'GenerateReport','off');

end
