% clear

tank_area = [4 5];                      %% 水槽の底面積
%%%%%%%hole_area = [1 2];                      %% 排水溝の面積
%%%%%%%C_plant = hole_area * sqrt(2*9.806);    %% トリチェリの定理より……
C_plant = [1 2];

state_eq_A = C_plant'*tank_area;

x_dim          = 2; %% 状態変数の数
realu_dim      = 2; %% 操作量の次元数（制約を等式制約に変換するために導入したダミー入力を含む）
dummyu_dim     = 0; %% ダミー入力の次元数
constraint_num = 0; %% 等式制約の数

delta_t     = 0.001;    %% シミュレーションのステップ幅
horizon_N   = 20;        %% 予測区間の分割数
horizon_tau = 0.002;     %% 予測区間の長さ

p_idx_Q  = diag([11 7]);   %% 二次形式評価関数の重み行列（区間）
p_idx_Sf = diag([2 2]);   %% 二次形式評価関数の重み行列（終端）
p_idx_r  = [1e-2 1e-2]; %% 評価関数の重みベクトル（入力値）

vector_size = (realu_dim + dummyu_dim + constraint_num) * horizon_N;
max_iteration = 3; %% GMRESの反復回数

% mpc_zeta = 1 / delta_t;

% fdgmres.mdlのVariant Subsystemの動作に必要
QR1 = Simulink.Variant('max_iteration ~= 1');
QR2 = Simulink.Variant('max_iteration == 1');