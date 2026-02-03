from dataclasses import dataclass
import swe_hw_1.domain.model as model

@dataclass
class CreateAliveArgs:
    type: model.AliveType
    name: str
    food: int
    kindness: int

@dataclass
class CreateAliveRes:
    id: str

@dataclass
class ListAlivesArgs:
    is_contact: bool

@dataclass
class ListAlivesRes:
    alives: list[model.Alive]

@dataclass
class GetAlivesFoodConsumptionArgs:
    pass

@dataclass
class GetAlivesFoodConsumptionRes:
    food: int
