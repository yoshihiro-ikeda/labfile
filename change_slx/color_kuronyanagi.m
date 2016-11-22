function color_kuronyanagi(sys)

load_system(sys);

blk = find_system(sys,'LookUnderMasks','all','Type','Block');

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

%disp(blk);

for i = 1:(numel(blk))
    
    set_param(char(blk(i,1)),'BackgroundColor','white');
end

colors = {'[1,0,0]'
        '[1,1,0]'
        '[0,0,1]'
        '[0,1,0]'
        '[0.6,0,1]'
        '[1,0,1]'
        '[1,0.8,0.6]'
        '[0.4,0,0.2]'
        '[1,0.4,0.2]'
        '[0.4,0.6,0.8]'
        '[1,0.4,0.6]'
        '[0,0,0.4]'
        '[0.8,1,0.8]'
        '[0.6,0.4,0.2]'
        '[0,0.4,0]'
        '[0.6,1.0,1.0]'};
    
%table = readtable('tmp_results.csv');
table = readtable('core.csv');
data = table2array(table(:,2:3));
name = table2cell(table(:,1));

disp(name);

for i = 1:length(blk)
    tmp = modname(char(blk(i,1)));
    disp(tmp);
    for j = 1:length(name)
        if strcmp(name(j,1),tmp)
            set_param(char(blk(i,1)),'BackgroundColor',char(colors(data(j,2)+1,1)));
            disp(char(blk(i,1)));
            disp(char(colors(data(j,2)+1,1)));
        end
    end
end