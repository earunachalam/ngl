    rootdir = '../data/';
    
    % get listing of all trajectories
    dirs = dir(rootdir);

    % get name of most recently created trajectories
    filename = dirs(size(dirs,1)).name;

    % directory of interest
    doi = [rootdir filename '/state'];
% 	cd(doi)
    A = csvread([doi '/0.csv']);
    B = csvread([doi '/1.csv']);
    A = A(1:(end-1),:);
    B = B(1:(end-1),:);
    A = sortrows(A,2); B = sortrows(B,2);
    A = A(:,5:6); B = B(:,5:6);
    C = A-B;
    D = C(:,1).^2 + C(:,2).^2; D = sqrt(D);
    plot(1:numel(D),D);
    ylim([0 50])