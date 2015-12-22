function csv2slx(sys)

exist_files(sys);

modelfile = sprintf('%s.slx',sys);
statefilename = sprintf('state_%s',modelfile);
statesys = sprintf('state_%s',sys);
outsys = sprintf('out_%s',sys);
outfilename = sprintf('out_%s',modelfile);
copyfile(modelfile,statefilename);
copyfile(modelfile,outfilename);

% 色付けツールでそれぞれの方程式を色付け
% コピー後のファイルに対してpaths.csvを更新する必要あり
mdltoxml(statesys,statesys);
close_system(statesys,0);
statexml = sprintf('%s.xml',statesys);
statecmd = sprintf('system(''./xmlreader %s'')',statexml);
eval(statecmd);
SetColorFromTaskMap(statesys,'result_state.csv','paths.csv');
save_system(statesys);

mdltoxml(outsys,outsys);
close_system(outsys,0);
outxml = sprintf('%s.xml',outsys);
outcmd = sprintf('system(''./xmlreader %s'')',outxml);
eval(outcmd);
SetColorFromTaskMap(outsys,'result_out.csv','paths.csv');
save_system(outsys);

% それぞれのモデルファイルを開いて色が付いているブロックを残して全て排除
deleteblk(statesys);
deleteblk(outsys);
% 矢印に対応したブロックを繋げる
disp('The block list of state equation');
add_outport(statesys);
disp('The block list of output equation');
add_inport(outsys);