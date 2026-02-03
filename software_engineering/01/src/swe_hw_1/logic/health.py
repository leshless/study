from dataclasses import dataclass
from abc import ABC, abstractmethod
from .health_dto import *
import swe_hw_1.domain.model as model
import swe_hw_1.util.rng as rng

ALIVE_HEALTHNESS_PROBABILITY = 0.85

class HealthController(ABC):
    @abstractmethod
    def check_alive_health(args: CheckAliveHealthArgs) -> CheckAliveHealthRes:
        pass

@dataclass
class HealthControllerImpl(HealthController):
    _rng: rng.RNG

    def check_alive_health(self, args: CheckAliveHealthArgs) -> CheckAliveHealthRes:
        is_healthy = self._rng.is_occured(ALIVE_HEALTHNESS_PROBABILITY)

        return CheckAliveHealthRes(is_healthy)