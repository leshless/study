from dataclasses import dataclass
import opyoid
import swe_hw_1.util.rng as rng
import swe_hw_1.logic as logic 
import swe_hw_1.domain.model as model
import swe_hw_1.repository as repository 
import swe_hw_1.cli as cli

@dataclass
class App:
    _rng: rng.RNG
    _repository: repository.Repository
    _alive_controller: logic.AliveController
    _health_controller: logic.HealthController
    _inventory_controller: logic.InventoryController
    _cli_facade: cli.Facade
    _cli_service: cli.Service

    def run(self):
        self._cli_service.run()

def init_app() -> App:
    injector = opyoid.Injector(bindings=[
        opyoid.SelfBinding(App),
        opyoid.ClassBinding(rng.RNG, rng.RNGImpl),
        opyoid.ClassBinding(repository.Repository, repository.RepositoryImpl),
        opyoid.ClassBinding(logic.AliveController, logic.AliveControllerImpl),
        opyoid.ClassBinding(logic.HealthController, logic.HealthControllerImpl),
        opyoid.ClassBinding(logic.InventoryController, logic.InventoryControllerImpl),
        opyoid.ClassBinding(cli.Facade, cli.FacadeImpl),
        opyoid.ClassBinding(cli.Service, cli.ServiceImpl),
    ])
    
    return injector.inject(App) 