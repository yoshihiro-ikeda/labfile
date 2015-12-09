function csv2slx(sys)

if exist 'result_state.csv' file ~= 2 | exit 'result_out.csv' ~= 2
    return;
end
modelfile = sprintf('%s.slx',sys);
statefilename = sprintf('state_%s',modelfile);
outfilename = sprintf('out_%s',modelfile);
copyfile(modelfile,statefilename);
copyfile(modelfile,outfilename);

% 色付けツールでそれぞれの方程式を色付け

% それぞれのモデルファイルを開いて色が付いているブロックを残して全て排除

% 矢印に対応したブロックを繋げる