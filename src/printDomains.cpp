#include "Kingdom.h"


#include "universal.h"

void Kingdom::printDomains(){

	std::ofstream testingDomains1("/home/easun/Dropbox/Research/Lin/ngl/testingDomains1.csv");
    std::ofstream testingDomains2("/home/easun/Dropbox/Research/Lin/ngl/testingDomains2.csv");
    std::ofstream testingDomains3("/home/easun/Dropbox/Research/Lin/ngl/testingDomains3.csv");
    std::ofstream testingDomains4("/home/easun/Dropbox/Research/Lin/ngl/testingDomains4.csv");
    std::ofstream testingDomains5("/home/easun/Dropbox/Research/Lin/ngl/testingDomains5.csv");
    std::ofstream testingDomains6("/home/easun/Dropbox/Research/Lin/ngl/testingDomains6.csv");
    std::ofstream testingDomains7("/home/easun/Dropbox/Research/Lin/ngl/testingDomains7.csv");
    std::ofstream testingDomains8("/home/easun/Dropbox/Research/Lin/ngl/testingDomains8.csv");
    std::ofstream testingDomains9("/home/easun/Dropbox/Research/Lin/ngl/testingDomains9.csv");
    std::ofstream testingDomains10("/home/easun/Dropbox/Research/Lin/ngl/testingDomains10.csv");

    for (int i = 0; i < Domains.size(); ++i){

    	for (int j = 0; j < Domains.at(i)->subdomains_center.size(); ++j){
    		
    		testingDomains1 << Domains.at(i)->subdomains_center.at(j)->north << "," << Domains.at(i)->subdomains_center.at(j)->west	<< std::endl;
    		if (!(Domains.at(i)->subdomains_center.at(j)->residents.empty())){std::for_each(Domains.at(i)->subdomains_center.at(j)->residents.begin(), Domains.at(i)->subdomains_center.at(j)->residents.end(),[&testingDomains10](std::shared_ptr<Sp>& object){P2S(object->id); testingDomains10 << object->x[1] << "," << object->x[0] << std::endl;});}
    	}

    	for (int j = 0; j < Domains.at(i)->subdomains_north.size(); ++j){
    		
    		testingDomains2 << Domains.at(i)->subdomains_north.at(j)->north	<< "," << Domains.at(i)->subdomains_north.at(j)->west << std::endl;
    		testingDomains3 << Domains.at(i)->subdomains_south.at(j)->north	<< "," << Domains.at(i)->subdomains_south.at(j)->west << std::endl;
    		testingDomains4 << Domains.at(i)->subdomains_east.at(j)->north << "," << Domains.at(i)->subdomains_east.at(j)->west	<< std::endl;
    		testingDomains5 << Domains.at(i)->subdomains_west.at(j)->north << "," << Domains.at(i)->subdomains_west.at(j)->west << std::endl;


            if (!(Domains.at(i)->subdomains_west.at(j)->residents.empty())){std::for_each(Domains.at(i)->subdomains_west.at(j)->residents.begin(), Domains.at(i)->subdomains_west.at(j)->residents.end(),[&testingDomains10](std::shared_ptr<Sp>& object){P2S(object->id); testingDomains10 << object->x[1] << "," << object->x[0] << std::endl;});}
            if (!(Domains.at(i)->subdomains_east.at(j)->residents.empty())){std::for_each(Domains.at(i)->subdomains_east.at(j)->residents.begin(), Domains.at(i)->subdomains_east.at(j)->residents.end(),[&testingDomains10](std::shared_ptr<Sp>& object){P2S(object->id); testingDomains10 << object->x[1] << "," << object->x[0] << std::endl;});}
            if (!(Domains.at(i)->subdomains_south.at(j)->residents.empty())){std::for_each(Domains.at(i)->subdomains_south.at(j)->residents.begin(), Domains.at(i)->subdomains_south.at(j)->residents.end(),[&testingDomains10](std::shared_ptr<Sp>& object){P2S(object->id); testingDomains10 << object->x[1] << "," << object->x[0] << std::endl;});}
            if (!(Domains.at(i)->subdomains_north.at(j)->residents.empty())){std::for_each(Domains.at(i)->subdomains_north.at(j)->residents.begin(), Domains.at(i)->subdomains_north.at(j)->residents.end(),[&testingDomains10](std::shared_ptr<Sp>& object){P2S(object->id); testingDomains10 << object->x[1] << "," << object->x[0] << std::endl;});}
    	}

        testingDomains6 << Domains.at(i)->subdomain_northwest->north << "," << Domains.at(i)->subdomain_northwest->west << std::endl;
        testingDomains7 << Domains.at(i)->subdomain_northeast->north << "," << Domains.at(i)->subdomain_northeast->west << std::endl;
        testingDomains8 << Domains.at(i)->subdomain_southwest->north << "," << Domains.at(i)->subdomain_southwest->west << std::endl;
        testingDomains9 << Domains.at(i)->subdomain_southeast->north << "," << Domains.at(i)->subdomain_southeast->west << std::endl;

        if (!(Domains.at(i)->subdomain_northwest->residents.empty())){std::for_each(Domains.at(i)->subdomain_northwest->residents.begin(), Domains.at(i)->subdomain_northwest->residents.end(),[&testingDomains10](std::shared_ptr<Sp>& object){P2S(object->id); testingDomains10 << object->x[1] << "," << object->x[0] << std::endl;});}
        if (!(Domains.at(i)->subdomain_southwest->residents.empty())){std::for_each(Domains.at(i)->subdomain_southwest->residents.begin(), Domains.at(i)->subdomain_southwest->residents.end(),[&testingDomains10](std::shared_ptr<Sp>& object){P2S(object->id); testingDomains10 << object->x[1] << "," << object->x[0] << std::endl;});}
        if (!(Domains.at(i)->subdomain_northeast->residents.empty())){std::for_each(Domains.at(i)->subdomain_northeast->residents.begin(), Domains.at(i)->subdomain_northeast->residents.end(),[&testingDomains10](std::shared_ptr<Sp>& object){P2S(object->id); testingDomains10 << object->x[1] << "," << object->x[0] << std::endl;});}
        if (!(Domains.at(i)->subdomain_southeast->residents.empty())){std::for_each(Domains.at(i)->subdomain_southeast->residents.begin(), Domains.at(i)->subdomain_southeast->residents.end(),[&testingDomains10](std::shared_ptr<Sp>& object){P2S(object->id); testingDomains10 << object->x[1] << "," << object->x[0] << std::endl;});}
	}
}

// in MATLAB, navigate to .../Conway6 and issue the following command:
// clf; for i = 1:10, A{i} = csvread(['testingDomains' num2str(i) '.csv']); scatter(A{i}(:,2),A{i}(:,1),'filled'); hold on; end; axis equal; saveas(gcf,'/home/easun/Desktop/testimg.png'); system('setsid viewnior /home/easun/Desktop/testimg.png')