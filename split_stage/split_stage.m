%filename : offset info file
function split_stage(sys,filename)

load_system(sys);

blk = find_system(sys,'LookUnderMasks','all','Type','Block');
%blk_list = find_system(sys,'LookUnderMasks','all','Type','Block');
blk_list = find_system(sys,'FindAll','On','type','Block');

%マスク関係のおまじない
for i = 1:(numel(blk))
    disp(blk(i));
    mtype = get_param(blk(i),'MaskType');
    disp('mtype');
    disp(mtype);
    if strcmp(mtype,'') == 0
        if strcmp(get_param(blk(i),'BlockType'),'S-Function')||strcmp(get_param(blk(i),'MaskType'),'Saturation Dynamic')
            continue;
        end
        childblks = get_param(blk(i),'Blocks');
        disp('child');
        disp(childblks);
        if iscell(childblks)
            for j=1:numel(childblks{1})
                bname = strcat(blk(i),'/',childblks{1}{j});
                blk{numel(blk)+1,1} = strjoin(bname,'');
            end
        else
            for j = 1:numel(childblks)
            bname = strcat(blk(i),'/',childblks(j)); 
            blk{numel(blk)+1,1} = strjoin(bname,'');
            end
        end
    end
end

table = readtable(filename);
data = table2array(table(:,2:3));
name = table2cell(table(:,1));

%disp(data);

disp('------------------------')

%
for i = 1:length(blk)
    tmp = modname(char(blk(i,1)));
    disp(tmp);
    for j = 1:length(name)
        if strcmp(name(j,1),tmp) && data(j,2) ~= -1
            try
                %sample_time = sprintf('[%f,%f]',rate_l,rate_s * data(j,2));
                stage_info = sprintf('%d',data(j,2));
                set_param(char(blk(i,1)),'Tag',stage_info);
            catch ME
                disp('error');
                disp(char(blk(i,1)));
            end
            %disp(char(colors(data(j,2)+1,1)));
        end
    end
end


id = 0;
gotolist = find_system(sys,'FindAll','on','Blocktype','Goto');

%接続先のブロックとタグを見比べて異なっていたらadd_unitdelayを呼び出し
for i = 1:length(blk_list)
    disp(get_param(blk_list(i),'name'));
    srcBH = get_param(blk_list(i),'Handle');
    %disp(srcBH);
    srcLH = get_param(srcBH,'LineHandles');
    %disp(srcLH.Outport);
    %disp(blk(i));
    %outport_num = size(srcLH.Outport,2);
    %stage_info = get_param(blk_list(i),'tag');
    try
        outport_num = size(srcLH.Outport,2);
        stage_info = get_param(blk_list(i),'tag');
    catch ME
        disp('empty');
        continue;
    end
    if isempty(stage_info)
        continue;
    end
    %goto-fromの間でタグが異なる場合の処理
    equalgotofrom = 1;
    if strcmp(get_param(srcBH,'blocktype'),'From')
        from_gototag = get_param(srcBH,'GotoTag');
        for j = 1:size(gotolist,1)
            goto_gototag = get_param(gotolist(j),'GotoTag');
            before_stage_info = get_param(gotolist(j),'tag');
            if isequal(goto_gototag,from_gototag) && isequal(stage_info,before_stage_info) == 0
                gotoLH = get_param(gotolist(j),'LineHandles');
                gotosrcBH = get_param(gotoLH.Inport,'SrcBlockHandle');
                try
                    id = add_unitdelay(sys,gotosrcBH,gotolist(j),id);
                    gotolist(j) = [];
                catch ME
                    disp(ME);
                end
                id = id + 1;
                equalgotofrom = 0;
                break;
            end
            
        end
    end
    if equalgotofrom == 1
        for j = 1:outport_num
            dstBH = get_param(srcLH.Outport(j),'DstBlockHandle');
            for k = 1:size(dstBH,1)
                next_stage_info = get_param(dstBH(k),'tag');
                if isempty(next_stage_info) 
                    continue;
                end
                if strcmp(get_param(dstBH(k),'Blocktype'),'UnitDelay')
                    continue;
                end
                if(isequal(stage_info,next_stage_info) == 0)
                    disp(get_param(blk_list(i),'name'));
                    id = add_unitdelay(sys,srcBH,dstBH(k),id);
                else
                    disp(blk_list(i));
                    id = id + 1;
                end
            end
        end
    end
end