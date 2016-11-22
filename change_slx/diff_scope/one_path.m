function one_path(sys,blockname,nextblockname)

load_system(sys);
tw_list = find_system(sys,'FindAll','on','Blocktype','ToWorkspace');
tw_num = size(tw_list); 

for k = 1:tw_num(1)
    tw_name = sprintf('simout_%s',get_param(tw_list(k),'name'));
    set_param(tw_list(k),'VariableName',tw_name);
end;
sim(sys,[0,65.989939200000000],simset('DstWorkspace','base'));

for k = 1:tw_num(1)
    tw_name = sprintf('simout_%s_after',get_param(tw_list(k),'name'));
    set_param(tw_list(k),'VariableName',tw_name);
end;
%指定した箇所にUnitDelayを挿入
srcBH = get_param(blockname,'Handle');
srcLH = get_param(srcBH,'LineHandles');
outport_num = size(srcLH.Outport);
i = 5;
for j = 1:outport_num(2)
    dstBH = get_param(srcLH.Outport(j),'DstBlockHandle');
    if isequal(get_param(dstBH,'name'),get_param(nextblockname,'name')) == 1
        add_place = get_param(srcBH,'Parent');
        add_blk_name = sprintf('%s/Unit Delay_%d',add_place,i);
        disp(add_blk_name);
        addBH = add_block('simulink/Discrete/Unit Delay',add_blk_name);
        dstPH = get_param(srcLH.Outport(j),'DstPortHandle');
        dstPNum = get_param(dstPH,'PortNumber');
        delete_line(srcLH.Outport(j));
        srcP = sprintf('%s/%d',get_param(srcBH,'name'),j);
        dstP = sprintf('%s/%d',get_param(dstBH,'name'),dstPNum);
        add_dstP = sprintf('Unit Delay_%d/1',i);
        add_srcP = sprintf('Unit Delay_%d/1',i);
        %Unit Delay�̓�͑��ɐM�����ڑ�
        addL1 = add_line(add_place,srcP,add_dstP);
        %Unit Delay�̏o�͑��ɐM�����ڑ�
        addL2 = add_line(add_place,add_srcP,dstP);
    end;
end;

sim(sys,[0,65.989939200000000],simset('DstWorkspace','base'));

disp(blockname);

for k = 1:tw_num(1)
    disp(get_param(tw_list(k),'name'));
    tw_name = sprintf('simout_%s',get_param(tw_list(k),'name'));
    tw_name_after = sprintf('simout_%s_after',get_param(tw_list(k),'name'));
    operation = sprintf('diff_graph(%s,%s)',tw_name,tw_name_after);
    evalin('base',operation);
end;

end