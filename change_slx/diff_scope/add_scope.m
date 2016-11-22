function add_scope(sys)

sysH = load_system(sys);
%ブロック名の一覧を取得
blk_list = find_system(sys,'FindAll','On','type','Block');
blk_list_size = size(blk_list);

for i = 1:blk_list_size(1)
    blkH = get_param(blk_list(i),'Handle');
    lineH = get_param(blkH,'LineHandles');
    disp(get_param(blkH,'name'));
    %終端ブロックであることの確認
    if isequal(lineH.Outport,[]) == 1 && isequal(lineH.Inport,[]) == 0 && isequal(get_param(blkH,'BlockType'),'SubSystem') == 0
        %サブシステム内のOutportブロックでないことの確認
        if isequal(get_param(blkH,'BlockType'),'Outport') == 1
            if isequal(get_param(get_param(blkH,'Parent'),'Type'),'block_diagram') == 1
                src_pH = get_param(lineH.Inport,'SrcPortHandle');
                src_pNum = get_param(src_pH,'PortNumber');
                srcP = sprintf('%s/%d',get_param(get_param(lineH.Inport,'SrcBlockHandle'),'Name'),src_pNum);
                add_place = get_param(blkH,'Parent');
                %ここで場所だけでなくブロックの名前指定しないといけない
                %×:mdl5 ○:mdl5/Tw
                add_blk_name = sprintf('%s/Tw_%s',add_place, get_param(blkH,'name'));
                disp(add_blk_name);
                add_blkH = add_block('simulink/Sinks/To Workspace',add_blk_name);
                simout = sprintf('simout_%s',get_param(add_blkH,'name'));
                set_param(add_blkH,'VariableName',simout);
                add_pH = get_param(add_blkH,'PortHandles');
                add_pNum = get_param(add_pH.Inport,'PortNumber');
                disp(srcP);
                disp(dstP);
                dstP = sprintf('Tw_%s/%d',get_param(blkH,'name'),add_pNum);
                add_line(add_place,srcP,dstP);
            end;
        else
            src_pH = get_param(lineH.Inport,'SrcPortHandle');
            src_pNum = get_param(src_pH,'PortNumber');
            srcP = sprintf('%s/%d',get_param(get_param(lineH.Inport,'SrcBlockHandle'),'Name'),src_pNum);
            add_place = get_param(blkH,'Parent');
            add_blk_name = sprintf('%s/Tw_%s',add_place, get_param(blkH,'name'));
            disp(add_blk_name);
            add_blkH = add_block('simulink/Sinks/To Workspace',add_blk_name);
            simout = sprintf('simout_%s',get_param(add_blkH,'name'));
            set_param(add_blkH,'VariableName',simout);
            add_pH = get_param(add_blkH,'PortHandles');
            add_pNum = get_param(add_pH.Inport,'PortNumber');
            dstP = sprintf('Tw_%s/%d',get_param(blkH,'name'),add_pNum);
            disp(srcP);
            disp(dstP);
            add_line(add_place,srcP,dstP);
        end;
    end;
end;

sysName = get_param(sysH,'FileName');
if isequal(strfind(sysName,'.mdl'),[]) == 0
    save_filename = sprintf('addTw_%s.mdl',sys);
    save_system(sys,save_filename);
elseif isequal(strfind(sysName,'.slx'),[]) == 0
    save_filename = sprintf('addTw_%s.slx',sys);
    save_system(sys,save_filename);
end;

