

%--------------------------------------------------%%
% samptime = 1e-5;     % Simulation Stepsize
ECU_MOTOR.Ts    = 1e-4;     % Step size (s) for deadtimeSimulation
% 
% % Motor power rate
% f_rate  = 100;              %��i��]���irps�j
% TrefMax = 80.0;              %��i�g���N�iNm�j
% P_rate  = TrefMax*f_rate*2*pi;   %��i�p���[�iW�j

% Motor parameters
MDL.MOTOR.R   = 0.7;               %��R(ohm)
MDL.MOTOR.p   = 2;                 %�ɑΐ�
MDL.MOTOR.Ld  = 5e-3;              %d���C���_�N�^���X�iH�j 
MDL.MOTOR.Lq  = 9e-3;              %q���C���_�N�^���X�iH�j
MDL.MOTOR.Rnt = 60*1.414/(1000/60*2*pi*MDL.MOTOR.p); %����(V�Es/rad)
MDL.MOTOR.JL  = 0.4; %0.3e-3;             %�������[�����g(kg�Em�O2)
MDL.MOTOR.KT  = 0.5*1.414;           %�g���N�萔( Nm/A)
MDL.MOTOR.F   = 0.005;                %�S���W��( Nm/(rad/s) )

% % Inveter parameters
% IDC = TrefMax /(1.5*MOTOR.p*MOTOR.Rnt); %��i�d��(A)
% % VDC = P_rate/IDC;         %��i�d��(V)
ECU_MOTOR.VDC = 350;
ECU_MOTOR.f_carrier = 4.5e3;           %PWM�L�����A���g��
ECU_MOTOR.deadtime = 3e-6;             % �f�b�h�^�C��(s)
ECU_MOTOR.dvsw = ECU_MOTOR.deadtime/(1/ECU_MOTOR.f_carrier/4);

% Controller parameters
ECU_MOTOR.Phase_Idq = pi/2;           %�d���i�p(rad)

ECU_MOTOR.wc   = 2*pi*500 * 0.20;     %�d������cutoff���g��(rad/s)
ECU_MOTOR.kp_d = ECU_MOTOR.wc*MDL.MOTOR.Ld;               %PI Propotional gain,id)        
ECU_MOTOR.kp_q = ECU_MOTOR.wc*MDL.MOTOR.Lq;               %PI Propotional gain,iq  
ECU_MOTOR.Ti_d = MDL.MOTOR.Ld/MDL.MOTOR.R;                %PI Integral gain,id
ECU_MOTOR.Ti_q = MDL.MOTOR.Lq/MDL.MOTOR.R;                %PI Integral gain,iq

ECU_MOTOR.wsc  = ECU_MOTOR.wc/10;ECU_MOTOR.wpi  = ECU_MOTOR.wc/100; %���x������g���͈�(rad/s)      
ECU_MOTOR.kp_v = MDL.MOTOR.JL*ECU_MOTOR.wsc/MDL.MOTOR.KT/2;         %PI Propotional gain,
ECU_MOTOR.ki_v = ECU_MOTOR.kp_v*ECU_MOTOR.wpi;            %PI Integral gain


% Parameters for observer and disturbance 
ECU_MOTOR.obs_onoff = 1;      % �O���I�u�U�[�o�[On/Off (1:on, 0:off)
ECU_MOTOR.Tff = 2e-4;
ECU_MOTOR.ff = 100;
ECU_MOTOR.R   = 0.7;               %��R(ohm)
ECU_MOTOR.p   = 2;                 %�ɑΐ�
ECU_MOTOR.Ld  = 5e-3;              %d���C���_�N�^���X�iH�j 
ECU_MOTOR.Lq  = 9e-3;              %q���C���_�N�^���X�iH�j
ECU_MOTOR.Rnt = 60*1.414/(1000/60*2*pi*ECU_MOTOR.p); %����(V�Es/rad)

% Load torque phase
ECU_MOTOR.Phase_Loadtorque = pi*3/2;  %�ipi/3����pi*3/2�܂Łj

% Observer  Parameters for sensorless control
ECU_MOTOR.alpha_obs = ECU_MOTOR.wc/(2*pi);
ECU_MOTOR.k1=2; ECU_MOTOR.k2 = 3*ECU_MOTOR.alpha_obs; ECU_MOTOR.k3 = ECU_MOTOR.alpha_obs^2;
ECU_MOTOR.I = [ 1 0 ; 0 1 ] ;
ECU_MOTOR.J = [ 0 -1; 1 0 ] ;
ECU_MOTOR.O = [ 0 0 ; 0 0 ] ;
ECU_MOTOR.B1 = ( 1/MDL.MOTOR.Ld ) * ECU_MOTOR.I ;

%mask�����p
Inertia = 0.02;
MaxRev = 4e3;
MinRev = 0;

R = MDL.MOTOR.R;
p = MDL.MOTOR.p;
Ld = MDL.MOTOR.Ld;
Lq = MDL.MOTOR.Lq;
Rnt = MDL.MOTOR.Rnt;
JL = MDL.MOTOR.JL;
KT = MDL.MOTOR.KT;
ff = ECU_MOTOR.ff;

Phase_Idq = ECU_MOTOR.Phase_Idq;
wc = ECU_MOTOR.wc;
kp_d = ECU_MOTOR.kp_d;
kp_q = ECU_MOTOR.kp_q;
Ti_d = ECU_MOTOR.Ti_d;
Ti_q = ECU_MOTOR.Ti_q;
wsc = ECU_MOTOR.wsc;
wpi = ECU_MOTOR.wpi;
kp_v = ECU_MOTOR.kp_v;
ki_v = ECU_MOTOR.ki_v;
obs_onoff = ECU_MOTOR.obs_onoff;
Tff = ECU_MOTOR.Tff;
ff = ECU_MOTOR.ff;
Phase_Loadtorque = ECU_MOTOR.Phase_Loadtorque;
alpha_obs = ECU_MOTOR.alpha_obs;
k1 = ECU_MOTOR.k1;
k2 = ECU_MOTOR.k2;
k3 = ECU_MOTOR.k3;
I = ECU_MOTOR.I;
J = ECU_MOTOR.J;
O = ECU_MOTOR.O;
B1 = ECU_MOTOR.B1;
R = ECU_MOTOR.R;
p = ECU_MOTOR.p;
Ld = ECU_MOTOR.Ld;
Lq = ECU_MOTOR.Lq;
Rnt = ECU_MOTOR.Rnt;
Ts = ECU_MOTOR.Ts;
VDC = ECU_MOTOR.VDC;
f_carrier = ECU_MOTOR.f_carrier;
dvsw = ECU_MOTOR.dvsw;


% %�ȉ�����ǉ�
% wc   = 2*pi*500;            %�d������cutoff���g��(rad/s)
% Ld = MDL.MOTOR.Ld;
% Lq = MDL.MOTOR.Lq;
% % Observer  Parameters for sensorless control
% alpha_obs = wc/(2*pi);
% k1=2; k2 = 3*alpha_obs; k3 = alpha_obs^2;
% I = [ 1 0 ; 0 1 ] ;
% J = [ 0 -1; 1 0 ] ;
% O = [ 0 0 ; 0 0 ] ;
% B1 = ( 1/Ld ) * I ;
% 
% wm_thresh = 31.4159;
% sampleT = ECU_MOTOR.Ts;
% Tfilter4w = 0.01;
% 
% % �����g�d��( Filter1,2 )Parameters ( If_HF, wi, wre)
% % If_HF = 0.9;
% If_HF = 3.5;
% wi = alpha_obs*2*pi;
% 
% wre = 0.15*2*(2*pi);  % electric speed at low speed range, wre��filter2��݌v����l�A�O�܂ŋ߂Â��l�Ƃ���B
% wm_thresh = wre/2/(2*pi)*5;  %�����g�d��̋@�B���xthresh�l,���̎��g���ȉ��ł���΁A�����g�����i�@wre/pairs�̐��{��ڈ��Ɂj
% wm_thresh = 2*pi*5;
% 
% 
% 
% numflt1 = [1 wi]*wi;
% numflt1_cross = wre*wi;
% denflt1 = [ 1 2*wi wi^2+wre^2 ];
% % figure(3); bode( numflt1, denflt1 );
% 
% % SYS4flt1 = tf(numflt1, denflt1);
% % SYS4flt1_cross = tf(numflt1_cross, denflt1);
% % dSYS4flt1=c2d(SYS4flt1,sampleT);
% % dSYS4flt1_cross=c2d(SYS4flt1_cross,sampleT);
% dSYS4flt1.num{1} = [0    0.2696   -0.1969];
% dSYS4flt1.den{1} = [1.0000   -1.4608    0.5335];
% dSYS4flt1_cross.num{1} = [0    0.2408    0.1953]*1e-4;
% dSYS4flt1_cross.den{1} = [1.0000   -1.4608    0.5335];
% 
% alpha0 = 2*pi*alpha_obs;
% 
% 
% alpha = alpha0; % wre>=alpha0
% % numflt2_H = [1 alpha] * (alpha^2+wre^2)/alpha;
% numflt2_H = [1 alpha]*alpha;
% numflt2_H_cross = wre*alpha;
% denflt2_H = [ 1 2*alpha alpha^2+wre^2 ];
% % figure(1); bode( numflt2_H, denflt2_H );
% 
% % SYS4flt2_H = tf(numflt2_H, denflt2_H);
% % SYS4flt2_H_cross = tf(numflt2_H_cross, denflt2_H);
% % dSYS4flt2_H=c2d(SYS4flt2_H,sampleT, 'tustin');
% % dSYS4flt2_H_cross=c2d(SYS4flt2_H_cross,sampleT, 'tustin');
% dSYS4flt2_H.num{1} = [0.1358    0.0369   -0.0989];
% dSYS4flt2_H.den{1} = [1.0000   -1.4570    0.5307];
% dSYS4flt2_H_cross.num{1} = [ 0.1106    0.2212    0.1106]*1e-4;
% dSYS4flt2_H_cross.den{1} = [1.0000   -1.4570    0.5307];
% 
% % alpha = wre;   % wre<alpha0
% alpha = wre*20;   % wre<alpha0
% % numflt2_L = [1 alpha] * (alpha^2+wre^2)/alpha;
% numflt2_L = [1 alpha]*alpha;
% numflt2_L_cross = wre*alpha;
% denflt2_L = [ 1 2*alpha alpha^2+wre^2 ];
% % figure(2); bode( numflt2_L, denflt2_L );
% 
% % SYS4flt2_L = tf(numflt2_L, denflt2_L);
% % SYS4flt2_L_cross = tf(numflt2_L_cross, denflt2_L);
% % dSYS4flt2_L=c2d(SYS4flt2_L,sampleT, 'tustin');
% % dSYS4flt2_L_cross=c2d(SYS4flt2_L_cross,sampleT, 'tustin');
% dSYS4flt2_L.num{1} = [ 0.0019    0.0000   -0.0019];
% dSYS4flt2_L.den{1} = [ 1.0000   -1.9925    0.9925];
% dSYS4flt2_L_cross.num{1} = [ 0.1770    0.3540    0.1770]*1e-6;
% dSYS4flt2_L_cross.den{1} = [ 1.0000   -1.9925    0.9925];
% 
% % �V�[�P���X
% Li = (Ld + Lq)/2;
% Lm = (Ld - Lq)/2;
% 
% %�@�O���I�u�U�[�o�[�萔
% MechDistobs_On  = 0;
% Tfilter4distobs = 0.125; %���萔
% JL = MDL.MOTOR.JL;
% F =MDL.MOTOR.F; 
% numLPfilter = [1];
% denLPfilter = [Tfilter4distobs 1];
% % SYS4LPfilter = tf(numLPfilter, denLPfilter);
% % dSYS4LPfilter=c2d(SYS4LPfilter,sampleT);
% dSYS4LPfilter.num{1} = [0    0.7997]*1e-3;
% dSYS4LPfilter.den{1} = [1.0000   -0.9992];
% 
% numEstim_withLPfilter = [JL F];
% denEstim_withLPfilter = [Tfilter4distobs 1];
% % SYS4Estim_withLPfilter = tf(numEstim_withLPfilter, denEstim_withLPfilter);
% % dSYS4Estim_withLPfilter=c2d(SYS4Estim_withLPfilter,sampleT);
% dSYS4Estim_withLPfilter.num{1} = [3.2000   -3.2000];
% dSYS4Estim_withLPfilter.den{1} = [1.0000   -0.9992];
% 
% % ��ߊE������
% WeakField_On=0;
% VDC=ECU_MOTOR.VDC;
% cv =  1 * VDC / sqrt(2);
% i_ref_max = 100;



