#include "include.h"
#include <math.h>
#include <time.h>

using namespace QMCm;

static Uniform uniform;

int main(int argc, char const *argv[]) {
SantoroTosattiMartonak stm;
stm.startingConfig.numberOfreplicas = 8;
stm.startingConfig.mainReplica.size = 8;
stm.startingConfig.mainReplica.generate();
  
  for (int i = 0; i < stm.startingConfig.nodes.size(); i++) {
    for (int j = 0; j < stm.startingConfig.nodes.size(); j++) {
      stm.startingConfig.nodes[i][j].value = 1;
      stm.startingConfig.nodes[i][j].spin  = (uniform() < 0.5) ? 1 : -1;
    }
  }
  
  for (int i = 0; i < stm.startingConfig.arcs.size(); i++)
    for (int j = 0; j < stm.startingConfig.arcs[i].size(); j++)
      for (int k = 0; k < stm.startingConfig.arcs[i][k].size(); k++)
        stm.startingConfig.arcs[i][j][k].value = 1;

  printf("The starting energy is [%f]\n", stm.startingConfig.getEnergy());
  for (int i = 0; i < 1000; i++) {
    clock_t time1, time2;
    time1 = clock();
    stm.run();
    time2 = clock();
    float time = (time2 - time1) / CLOCKS_PER_SEC;
    printf("The ending energy is [%f], and the runtime is [%f]\n", stm.endingConfig.getEnergy(), time);
  }
}
