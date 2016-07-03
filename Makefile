include ~/makefile.$(OS)

MMLCURRENTINCLPATH=/usr/local/include
# MMLCURRENTINCLPATH=/home1/04048/easun/include
CXXFLAGS=-O4 -g -ggdb -march=native -std=c++11 -isystem $(PLATFORMSPECIFICCXXFLAGS)
LINKFLAGS=$(CXXFLAGS)
VPATH=src

SRC=src
BIN=bin
OBJ=obj

BAREBONES=universal.h parameters.h

ALLOBJS=assignDomain.o assignDomains.o attemptMutation.o center.o cleanup.o collectAllObjects.o collectStatistics.o ConsumptionEvent.o createConsumptionEvents.o defineDomains.o defineSubdomains.o displayNetworkParameters.o divide.o Domain.o edge.o evict.o export.o findDomain.o getConnectivity.o getObjectNodeCount.o indexNetwork.o initialize.o interparticle.o ipAttraction.o ipRepulsion.o Kingdom.o main.o modifyConnectivity.o modulateInteractionStrength.o Neighbor.o Network.o nodeIndexToPosition.o nodeIndexToValue.o nwx.o outOfBounds.o overlapSingle.o populate.o positionToNodeIndex.o printDomains.o processEvent.o propagate.o proposeConsumption.o proposeDivision.o resetAllObjects.o run.o Sp.o Subdomain.o trade.o updatePositions.o updateProperties.o updateValues.o wrap.o

ALLOBJSDIR=$(addprefix $(OBJ)/, $(ALLOBJS))

all: $(BIN)/ngl.x

$(BIN)/ngl.x: $(ALLOBJSDIR) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) $(ALLOBJSDIR) -o $(BIN)/ngl.x

obj/assignDomain.o: $(SRC)/assignDomain.cpp $(BAREBONES) Domain.h Kingdom.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/assignDomains.o: $(SRC)/assignDomains.cpp $(BAREBONES) Domain.h Kingdom.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/attemptMutation.o: $(SRC)/attemptMutation.cpp $(BAREBONES) Domain.h Network.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/center.o: $(SRC)/center.cpp $(BAREBONES) distance.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/cleanup.o: $(SRC)/cleanup.cpp $(BAREBONES) Domain.h Kingdom.h Sp.h Subdomain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/collectAllObjects.o: $(SRC)/collectAllObjects.cpp $(BAREBONES) Domain.h Sp.h Subdomain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/collectStatistics.o: $(SRC)/collectStatistics.cpp $(BAREBONES) Domain.h Network.h Sp.h Subdomain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/ConsumptionEvent.o: $(SRC)/ConsumptionEvent.cpp $(BAREBONES) ConsumptionEvent.h Domain.h Neighbor.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/createConsumptionEvents.o: $(SRC)/createConsumptionEvents.cpp $(BAREBONES) ConsumptionEvent.h distance.h Domain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/defineDomains.o: $(SRC)/defineDomains.cpp $(BAREBONES) Domain.h mkdir.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/defineSubdomains.o: $(SRC)/defineSubdomains.cpp $(BAREBONES) Domain.h Neighbor.h Subdomain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/displayNetworkParameters.o: $(SRC)/displayNetworkParameters.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/divide.o: $(SRC)/divide.cpp $(BAREBONES) Domain.h force.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Domain.o: $(SRC)/Domain.cpp $(BAREBONES) ConsumptionEvent.h Domain.h force.h Neighbor.h Subdomain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/edge.o: $(SRC)/edge.cpp $(BAREBONES) distance.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/evict.o: $(SRC)/evict.cpp $(BAREBONES) Kingdom.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/export.o: $(SRC)/export.cpp $(BAREBONES) Kingdom.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/findDomain.o: $(SRC)/findDomain.cpp $(BAREBONES) Domain.h Kingdom.h Sp.h Subdomain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/getConnectivity.o: $(SRC)/getConnectivity.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/getObjectNodeCount.o: $(SRC)/getObjectNodeCount.cpp $(BAREBONES) Domain.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/indexNetwork.o: $(SRC)/indexNetwork.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/initialize.o: $(SRC)/initialize.cpp $(BAREBONES) Kingdom.h overlapSingle.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/interparticle.o: $(SRC)/interparticle.cpp $(BAREBONES) distance.h Domain.h force.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/ipAttraction.o: $(SRC)/ipAttraction.cpp $(BAREBONES) distance.h force.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/ipRepulsion.o: $(SRC)/ipRepulsion.cpp $(BAREBONES) distance.h force.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Kingdom.o: $(SRC)/Kingdom.cpp $(BAREBONES) Kingdom.h mkdir.h overlapSingle.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/main.o: $(SRC)/main.cpp $(BAREBONES) $(SRC)/Kingdom.cpp Kingdom.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/modifyConnectivity.o: $(SRC)/modifyConnectivity.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/modulateInteractionStrength.o: $(SRC)/modulateInteractionStrength.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Neighbor.o: $(SRC)/Neighbor.cpp $(BAREBONES) Neighbor.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Network.o: $(SRC)/Network.cpp $(BAREBONES) Network.h AdderLogisticNode.h GenericDownstreamNode.h MultiplierNode.h Node.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/nodeIndexToPosition.o: $(SRC)/nodeIndexToPosition.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/nodeIndexToValue.o: $(SRC)/nodeIndexToValue.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/nwx.o: $(SRC)/nwx.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/outOfBounds.o: $(SRC)/outOfBounds.cpp $(BAREBONES) Sp.h $(SRC)/Subdomain.cpp Subdomain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/overlapSingle.o: $(SRC)/overlapSingle.cpp $(BAREBONES) $(SRC)/distance.h $(SRC)/Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@	

obj/populate.o: $(SRC)/populate.cpp $(BAREBONES) Domain.h Kingdom.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/positionToNodeIndex.o: $(SRC)/positionToNodeIndex.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/printDomains.o: $(SRC)/printDomains.cpp $(BAREBONES) Kingdom.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/processEvent.o: $(SRC)/processEvent.cpp $(BAREBONES) ConsumptionEvent.h Domain.h Kingdom.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/propagate.o: $(SRC)/propagate.cpp $(BAREBONES) ConsumptionEvent.h Domain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/proposeConsumption.o: $(SRC)/proposeConsumption.cpp $(BAREBONES) ConsumptionEvent.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/proposeDivision.o: $(SRC)/proposeDivision.cpp $(BAREBONES) distance.h Domain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/resetAllObjects.o: $(SRC)/resetAllObjects.cpp $(BAREBONES) Domain.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/run.o: $(SRC)/run.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Sp.o: $(SRC)/Sp.cpp $(BAREBONES) Network.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Subdomain.o: $(SRC)/Subdomain.cpp $(BAREBONES) Sp.h Subdomain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/trade.o: $(SRC)/trade.cpp $(BAREBONES) Kingdom.h Neighbor.h Sp.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/updatePositions.o: $(SRC)/updatePositions.cpp $(BAREBONES) Domain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/updateProperties.o: $(SRC)/updateProperties.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/updateValues.o: $(SRC)/updateValues.cpp $(BAREBONES) Network.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/wrap.o: $(SRC)/wrap.cpp $(BAREBONES) distance.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o obj/*.o obj/*.gch $(BIN)/ngl.x

.phony: all clean
