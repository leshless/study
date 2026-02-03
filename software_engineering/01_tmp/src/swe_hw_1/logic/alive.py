from dataclasses import dataclass
from .alive_dto import *
from .health_dto import *
from .health import *
import swe_hw_1.domain.model as model
import swe_hw_1.domain.error as error
import swe_hw_1.util.rng as rng
import swe_hw_1.repository as repository

MINIMAL_CONTACT_ALIVE_KINDNESS = 5

class AliveController(ABC):
    @abstractmethod
    def create_alive(args: CreateAliveArgs) -> CreateAliveRes:
        pass

    @abstractmethod
    def list_alives(args: ListAlivesArgs) -> ListAlivesRes:
        pass

    @abstractmethod
    def get_alives_food_consumption(args: GetAlivesFoodConsumptionArgs) -> GetAlivesFoodConsumptionRes:
        pass

@dataclass
class AliveControllerImpl(AliveController):
    _health_controller: HealthController
    _repository: repository.Repository
    _rng: rng.RNG

    def create_alive(self, args: CreateAliveArgs) -> CreateAliveRes:
        alive_id = self._rng.ulid()

        match args.type:
            case model.AliveType.MONKEY:
                alive = model.Monkey(alive_id, args.name, args.food, args.kindness)
            case model.AliveType.RABBIT:
                alive = model.Rabbit(alive_id, args.name, args.food, args.kindness)
            case model.AliveType.TIGER:
                alive = model.Tiger(alive_id, args.name, args.food)
            case model.AliveType.WOLF:
                alive = model.Wolf(alive_id, args.name, args.food)
            case _:
                raise error.UnkownAliveTypeError

        res = self._health_controller.check_alive_health(alive)
        if not res.is_healthy:
            raise error.AliveIsNotHealthyError
        
        self._repository.insert_alive(alive)

        return CreateAliveRes(id=alive_id)


    def list_alives(self, args: ListAlivesArgs) -> ListAlivesRes:
        alives = self._repository.list_alives()

        alives.sort(key = lambda alive : alive.name)
        
        if args.is_contact:
            alives = list(filter(lambda alive : isinstance(alive, model.Herbo) and alive.kindness >= MINIMAL_CONTACT_ALIVE_KINDNESS, alives))
        
        return ListAlivesRes(alives=alives)

    
    def get_alives_food_consumption(self, args: GetAlivesFoodConsumptionArgs) -> GetAlivesFoodConsumptionRes:
        alives = self._repository.list_alives()
        alives_food = sum(list(map(lambda alive : alive.food, alives)))

        return GetAlivesFoodConsumptionRes(food=alives_food)