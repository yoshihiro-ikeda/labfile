% clear

tank_area = [4 5];                      %% �����̒�ʐ�
%%%%%%%hole_area = [1 2];                      %% �r���a�̖ʐ�
%%%%%%%C_plant = hole_area * sqrt(2*9.806);    %% �g���`�F���̒藝���c�c
C_plant = [1 2];

state_eq_A = C_plant'*tank_area;

x_dim          = 2; %% ��ԕϐ��̐�
realu_dim      = 2; %% ����ʂ̎������i����𓙎�����ɕϊ����邽�߂ɓ��������_�~�[���͂��܂ށj
dummyu_dim     = 0; %% �_�~�[���͂̎�����
constraint_num = 0; %% ��������̐�

delta_t     = 0.001;    %% �V�~�����[�V�����̃X�e�b�v��
horizon_N   = 20;        %% �\����Ԃ̕�����
horizon_tau = 0.002;     %% �\����Ԃ̒���

p_idx_Q  = diag([11 7]);   %% �񎟌`���]���֐��̏d�ݍs��i��ԁj
p_idx_Sf = diag([2 2]);   %% �񎟌`���]���֐��̏d�ݍs��i�I�[�j
p_idx_r  = [1e-2 1e-2]; %% �]���֐��̏d�݃x�N�g���i���͒l�j

vector_size = (realu_dim + dummyu_dim + constraint_num) * horizon_N;
max_iteration = 3; %% GMRES�̔�����

% mpc_zeta = 1 / delta_t;

% fdgmres.mdl��Variant Subsystem�̓���ɕK�v
QR1 = Simulink.Variant('max_iteration ~= 1');
QR2 = Simulink.Variant('max_iteration == 1');