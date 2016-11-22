function color_ori(sys)

load_system(sys);

blk = find_system(sys,'LookUnderMasks','all','Type','Block');

for i = 1:(numel(blk))
    disp(blk(i));
    mtype = get_param(blk(i),'MaskType');
    if strcmp(mtype,'') == 0
        childblks = get_param(blk(i),'Blocks');
        for j = 1:(numel(childblks))
            bname = strcat(blk(i),'/',childblks(j));
            blk{numel(blk)+1,1} = strjoin(bname,'');
        end
    end
end

disp(blk);

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
    
table = readtable('tmp_results.csv');
data = table2array(table(:,2:3));
name = table2cell(table(:,1));

for i = 1:length(blk)
    tmp = modname(char(blk(i,1)));
    for j = 1:length(name)
        if strcmp(name(j,1),tmp)
            set_param(char(blk(i,1)),'BackgroundColor',char(colors(data(j,2)+1,1)));
        end
    end
end