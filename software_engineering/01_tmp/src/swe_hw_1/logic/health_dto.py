from dataclasses import dataclass
import swe_hw_1.domain.model as model

@dataclass
class CheckAliveHealthArgs:
    alive: model.Alive

@dataclass
class CheckAliveHealthRes:
    is_healthy: bool
