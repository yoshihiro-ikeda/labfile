%sys:���̓��f����
%filename:path��csv�t�@�C��

function diff_scope(sys,filename)

load_system(sys);
fileID = fopen(filename);
path = textscan(fileID,'%s');
path_size = size(path{1});

for i = 1:path_size(1)
    path{1}{i} = sprintf('addTw_%s',path{1}{i});
end;

celldisp(path);

tw_list = find_system(sys,'FindAll','on','Blocktype','ToWorkspace');
tw_num = size(tw_list); 

for i = 1:path_size(1)-1
    %������To Workspace�u���b�N�̏o�͑Ώۂ̕ϐ�����ύX
    %�ϐ�����simout_Tw_�u���b�N��_Num
    for k = 1:tw_num(1)
        tw_name = sprintf('simout_%s_%d',get_param(tw_list(k),'name'),i);
        set_param(tw_list(k),'VariableName',tw_name);
    end;
    disp(i);
    srcBH = get_param(path{1}{i},'Handle');
    srcLH = get_param(srcBH,'LineHandles');
    %�Ƃ肠�����ڑ��悪SubSystem�̏ꍇ
    %���݂̃u���b�N��SubSystem���̍Ō�̃u���b�N�̏ꍇ�͍l���Ȃ�
    outport_num = size(srcLH.Outport);
    for j = 1:outport_num(2)
        dstBH = get_param(srcLH.Outport(j),'DstBlockHandle');
        if isequal(get_param(dstBH,'name'),get_param(path{1}{i+1},'name')) == 1
            add_place = get_param(srcBH,'Parent');
            add_blk_name = sprintf('%s/Unit Delay_%d',add_place,i);
            disp(add_blk_name);
            addBH = add_block('simulink/Discrete/Unit Delay',add_blk_name);
            %addPH = get_param(addBH,'PortHandles');
            dstPH = get_param(srcLH.Outport(j),'DstPortHandle');
            dstPNum = get_param(dstPH,'PortNumber');
            delete_line(srcLH.Outport(j));
            srcP = sprintf('%s/%d',get_param(srcBH,'name'),j);
            dstP = sprintf('%s/%d',get_param(dstBH,'name'),dstPNum);
            add_dstP = sprintf('Unit Delay_%d/1',i);
            add_srcP = sprintf('Unit Delay_%d/1',i);
            %Unit Delay�̓��͑��ɐM������ڑ�
            addL1 = add_line(add_place,srcP,add_dstP);
            %Unit Delay�̏o�͑��ɐM������ڑ�
            addL2 = add_line(add_place,add_srcP,dstP);
            %�V�~�����[�V���������s
            %simout = sim(sys);
            sim(sys,[0,65.989939200000000],simset('DstWorkspace','base'));
            %sim(sys,'ReturnWorkspaceOutputs','on');
            %�ǉ������M���������UnitDelay���폜
            %�M���������̂悤�ɕ���
            delete_line(addL1);
            delete_line(addL2);
            delete_block(addBH);
            add_line(add_place,srcP,dstP);
            disp('hello');
        end;
    end;
end;