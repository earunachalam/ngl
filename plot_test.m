clear; clc; clf;


A = csvread('rec.csv');


subplot(2,2,1);
hold on;
plot(A(:,1), A(:,3));
plot(A(:,1), A(:,2),'r'); axis square; 
title('\boldmath$MSD(t)$','interpreter','latex')
xlabel('\boldmath$time (s)$','interpreter','latex'); ylabel('\boldmath$MSD (m^2)$','interpreter','latex');

subplot(2,2,2); 
hold on;
plot(A(:,1), A(:,5));
plot(A(:,1), A(:,4),'r'); axis square; 
title('\boldmath$MSD(t)$','interpreter','latex')
xlabel('\boldmath$time (s)$','interpreter','latex'); ylabel('\boldmath$MSD (rad^2)$','interpreter','latex');

subplot(2,2,3);
mean(A(:,4))
hold on;
plot(A(:,1), A(:,6)); plot(A(:,1), 4.1124e-21*ones(size(A,1),1),'r'); axis square; ylim([0e-21 4.5e-21]);
title('\boldmath$KE^{(trans)}_{avg}(t)$','interpreter','latex')
xlabel('\boldmath$time (s)$','interpreter','latex'); ylabel('\boldmath$KE (J)$','interpreter','latex');


subplot(2,2,4);
hold on;
plot(A(:,1), A(:,7)); plot(A(:,1), 2.0562e-21*ones(size(A,1),1),'r'); axis square; ylim([0e-21 2.5e-21]);
title('\boldmath$KE^{(rot)}_{avg}(t)$','interpreter','latex')
xlabel('\boldmath$time (s)$','interpreter','latex'); ylabel('\boldmath$KE (J)$','interpreter','latex');