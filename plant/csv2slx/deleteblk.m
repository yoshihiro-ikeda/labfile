function deleteblk(sys)

load_system(sys);
blk_list = find_system(sys,'Type','Block');
blk_num = size(blk_list);

line_list = find_system(sys,'FindAll','On','type','line');
line_num = size(line_list);

%重複する信号線を排除
delete_line_list = line_list;
count = 0;
for i = 1:line_num(1)
    blkH_line_out = get_param(line_list(i),'DstBlockHandle');
    dstsize = size(blkH_line_out);
    if dstsize(1) ~= 1
        delete_line_list(i - count) = [];
        count = count + 1;
    end
end

line_list = delete_line_list;
line_num = size(line_list);

count = 1;
delete_line_list = [];

%行き先が黄色のブロックの信号線を排除
for i = 1:line_num(1)
    blkH_line_out = get_param(line_list(i),'DstBlockHandle');
    dstsize = size(blkH_line_out);
    for j = 1:dstsize(1)
        if strcmp(get_param(blkH_line_out(j),'BackgroundColor'), '[1.000000, 0.000000, 0.000000]')
            %delete_line(line_list(i));
            delete_line_list(count) = line_list(i);
            count = count + 1;
        end
    end
end

delete_num = size(delete_line_list);

for i = 1:delete_num(2)
    delete_line(delete_line_list(i));
end

%黄色のブロックを排除
for i = 1:blk_num(1)
    tmp_blk = blk_list(i);
    if strcmp(get_param(tmp_blk,'BackgroundColor'), '[1.000000, 0.000000, 0.000000]')
        delete_block(tmp_blk);
    end
end
