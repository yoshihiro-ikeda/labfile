function mdl2para(sys)

m2x_ans = input('execute mdltoxml? (y/n):','s');
if m2x_ans == 'y'
    addpath(genpath('/home/yoshi12/matlab/git/Lab/mdltoxml'));
    mdltoxml(sys,sys);
end

code = input('execute generating code? (y/n):','s');
if code == 'y'
    %コード生成コマンド
end

inst = sprintf('../myinit.sh %s',sys);
system(inst);

end