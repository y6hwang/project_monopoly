CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = monopoly
OBJECTS = main.o textdisplay.o bank.o view.o professor.o student.o goose.o pinktie.o thd.o laptop.o money.o grt.o controller.o c2.o dc.o coopfee.o Game.o cif.o dctimline.o GameNotification.o player.o al.o art1.o art2.o b1.o b2.o bmh.o board.o cph.o dwe.o ech.o eit.o engineering.o environment.o science1.o esc.o ev1.o ev2.o ev3.o goosenesting.o gototims.o gym.o health.o hh.o improvable.o lhi.o math.o mc.o mkv.o ml.o nh.o nonimprovable.o nonproperty.o opt.o osap.o pac.o pas.o phys.o property.o rch.o residence.o rev.o rollrims.o science2.o slc.o tuition.o uwp.o v1.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

.PHONY: clean
