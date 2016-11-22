%ブロックを2つ指定して指定してその間のブロックのパスを取得

function between_blks(sys,srcblk,dstblk)

load_system(sys);
srcblkH = get_param(srcblk,'Handle');
%ソースブロックからのアウトプットブロックリストを取得
srcoutList = get_param(srcblkH,'outputsignals')
