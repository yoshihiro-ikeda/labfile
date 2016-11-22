function hilight_path(sys,filename)

%モデルをロード
sysH = load_system(sys);

%パスファイルをロード
%path        パスのブロックリスト
%path_size:  パスのブロック数

fileID = fopen(filename);
path = textscan(fileID,'%s');
path_size = size(path{1});

%すべてのブロックのbackcolorを黒に変更
allblkList = find_system(sysH,'FindAll','On','type','block');
blknum = size(allblkList);
for i = 1:blknum(1)
    set_param(allblkList(i),'ForegroundColor','black');
    set_param(allblkList(i),'BackgroundColor','gray');
end;

%モデルの背景をグレーに
set_param(sysH,'screenColor','gray');
subsysList = find_system(sysH,'blocktype','SubSystem');
subsysListSize = size(subsysList);
for i = 1:subsysListSize(1)
	  set_param(subsysList(i),'screenColor','gray');
end;

%パスのブロックリストのブロックを色変更
for i = 1:path_size(1)
    blkH = get_param(path{1}{i},'Handle');
    set_param(blkH,'BackgroundColor','magenta');
	set_param(blkH,'ForegroundColor','black');
end;

%サブシステムを塗る処理
for i = 1:path_size(1)
    blkH = get_param(path{1}{i},'Handle');
    blk_prt = get_param(blkH,'Parent');
    if strcmp(blk_prt,sys) == 0
        set_param(blk_prt,'BackgroundColor','magenta');
    end;
end;

%片方でも接続先のブロックの色がmagentaの場合サブシステムの色を変更
% for i = 1:subsysListSize(1)
%     subH = get_param(subsysList(i),'LineHandles');
%     numIn = size(subH.Inport);
%     numOut = size(subH.Outport);
%     for j = 1:numIn(2)
%         if strcmp(get_param(get_param(subH.Inport(j),'SrcBlockHandle'),'BackgroundColor'),'magenta')
%             set_param(subsysList(i),'BackgroundColor','magenta');
%         end;
%     end;
%     for j = 1:numOut(2)
%         if strcmp(get_param(get_param(subH.Outport(j),'DstBlockHandle'),'BackgroundColor'),'magenta')
%             set_param(subsysList(i),'BackgroundColor','magenta');
%         end;
%     end;    
% end;

