class AliveAlreadyExistsError(Exception):
    def __str__(self):
        return "Animal already exists"

class AliveIsNotHealthyError(Exception):
    def __str__(self):
            return "Animal is not healthy"

class UnkownAliveTypeError(Exception):
    def __str__(self):
            return "Unknown animal type"
