function return_id = add_unitdelay(sys,blockname,nextblockname,id)

load_system(sys);
tw_list = find_system(sys,'FindAll','on','Blocktype','ToWorkspace');
tw_num = size(tw_list); 

for k = 1:tw_num(1)
    tw_name = sprintf('simout_%s',get_param(tw_list(k),'name'));
    set_param(tw_list(k),'VariableName',tw_name);
end;
%sim(sys,[0,65.989939200000000],simset('DstWorkspace','base'));

for k = 1:tw_num(1)
    tw_name = sprintf('simout_%s_after',get_param(tw_list(k),'name'));
    set_param(tw_list(k),'VariableName',tw_name);
end;
%指定した箇所にUnitDelayを挿入
srcBH = get_param(blockname,'Handle');
srcLH = get_param(srcBH,'LineHandles');
%disp(srcLH);
outport_num = size(srcLH.Outport,2);

targetBH = get_param(nextblockname,'Handle');
i = id;
%srcブロックの出力数でループ
for j = 1:outport_num
    dstBH = get_param(srcLH.Outport(j),'DstBlockHandle');
    dstPH = get_param(srcLH.Outport(j),'DstPortHandle');
    srcPH = get_param(srcLH.Outport(j),'SrcPortHandle');
    
    disp(size(dstBH,1));
    %srcブロックからの信号線が分岐した場合のループ
    for k = 1:size(dstBH,1)
        if isequal(get_param(dstBH(k),'name'),get_param(nextblockname,'name')) == 1
            disp('ok');
            try
                delete_line(srcLH.Outport(j));
            catch ME
                disp('already delete');
            end
            add_place = get_param(srcBH,'Parent');
            add_blk_name = sprintf('%s/Unit Delay_%d',add_place,i);
            disp(add_blk_name);            
            dstPNum = get_param(dstPH(k),'PortNumber');         
            srcP = sprintf('%s/%d',get_param(srcBH,'name'),j);
            dstP = sprintf('%s/%d',get_param(dstBH(k),'name'),dstPNum);
            add_dstP = sprintf('Unit Delay_%d/1',i);
            add_srcP = sprintf('Unit Delay_%d/1',i);
            %追加するUnitDelayの座標計算
            srcPosition = get_param(srcPH,'Position');
            dstPosition = get_param(dstPH(k),'Position');
            disp(srcPosition);
            disp(dstPosition);
            if srcPosition(1) + 100 < dstPosition(1)
                position = [100 120 140 160];
                position(1) = ((srcPosition(1) + dstPosition(1)) / 2) - 20;
                position(2) = ((srcPosition(2) + dstPosition(2)) / 2) - 20;
                position(3) = ((srcPosition(1) + dstPosition(1)) / 2) + 20;
                position(4) = ((srcPosition(2) + dstPosition(2)) / 2) + 20;
                addBH = add_block('simulink/Discrete/Unit Delay',add_blk_name,'position',position);
            elseif srcPosition(1) < dstPosition(1)
                position = [100 120 140 160];
                position(1) = ((srcPosition(1) + dstPosition(1)) / 2) - 1;
                position(2) = ((srcPosition(2) + dstPosition(2)) / 2) - 1;
                position(3) = ((srcPosition(1) + dstPosition(1)) / 2) + 1;
                position(4) = ((srcPosition(2) + dstPosition(2)) / 2) + 1;
                addBH = add_block('simulink/Discrete/Unit Delay',add_blk_name,'position',position);
            else
                addBH = add_block('simulink/Discrete/Unit Delay',add_blk_name);
            end;
            addL1 = add_line(add_place,srcP,add_dstP,'autorouting','on');
            addL2 = add_line(add_place,add_srcP,dstP,'autorouting','on');
            i = i + 1;
        end;
    end;
    disp(k);
    %一つの信号線から分岐させた場合の復元
    for l = 1:size(dstBH,1)
        %if l ~= k
        if 1 
            add_place = get_param(srcBH,'Parent');
            dstPNum = get_param(dstPH(l),'PortNumber');
            dstP = sprintf('%s/%d',get_param(dstBH(l),'name'),dstPNum);
            srcP = sprintf('%s/%d',get_param(srcBH,'name'),j);
            try
                add_line(add_place,srcP,dstP,'autorouting','on');
                disp('success');
            catch ME
                disp('error');
            end
        end
    end
end;

%sim(sys,[0,65.989939200000000],simset('DstWorkspace','base'));

%disp(blockname);

for k = 1:tw_num(1)
    %disp(get_param(tw_list(k),'name'));
    tw_name = sprintf('simout_%s',get_param(tw_list(k),'name'));
    tw_name_after = sprintf('simout_%s_after',get_param(tw_list(k),'name'));
    operation = sprintf('diff_graph(%s,%s)',tw_name,tw_name_after);
    %evalin('base',operation);
end;

return_id = i;

end