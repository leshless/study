from abc import ABC, abstractmethod
from dataclasses import dataclass
import random
import ulid

class RNG(ABC):
    @abstractmethod
    def is_occured(probability: float) -> bool:
        pass

    @abstractmethod
    def ulid() -> str:
        pass

class RNGImpl(RNG):
    def is_occured(self, probability: float) -> bool:
        return (random.random() <= probability)

    def ulid(self) -> str:
        return str(ulid.ULID())