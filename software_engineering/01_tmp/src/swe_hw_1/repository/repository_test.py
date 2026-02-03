import pytest
import collections
from swe_hw_1.repository import *
import swe_hw_1.domain.model as model
import swe_hw_1.domain.error as error

@pytest.fixture
def repository():
    return RepositoryImpl()

class TestUserSuite:
    def test_insert_and_list_alives_happy_path(self, repository):
        tiger = model.Tiger(
            id="some_id1",
            name="some_name",
            food=99
        )
        rabbit = model.Rabbit(
            id="some_id2",
            name="some_name",
            food=9,
            kindness=5
        )

        repository.insert_alive(tiger)
        repository.insert_alive(rabbit)

        alives = repository.list_alives()
        assert collections.Counter(alives) == collections.Counter([tiger, rabbit])

    def test_insert_alive_already_exists(self, repository):
        tiger = model.Tiger(
            id="some_id",
            name="some_name",
            food=99
        )
        rabbit = model.Rabbit(
            id="some_id",
            name="some_name",
            food=9,
            kindness=5
        )

        repository.insert_alive(tiger)
        
        with pytest.raises(error.AliveAlreadyExistsError):
            repository.insert_alive(rabbit)

        alives = repository.list_alives()
        assert collections.Counter(alives) == collections.Counter([tiger])

    def test_insert_and_list_inventories_happy_path(self, repository):
        table = model.Table(
            id="some_id1",
            name="some_name",
            number=99
        )
        computer = model.Computer(
            id="some_id2",
            name="some_name",
            number=99
        )

        repository.insert_inventory(table)
        repository.insert_inventory(computer)

        inventories = repository.list_inventories()
        assert collections.Counter(inventories) == collections.Counter([table, computer])

    def test_insert_inventory_already_exists(self, repository):
        table = model.Table(
            id="some_id",
            name="some_name",
            number=99
        )
        computer = model.Computer(
            id="some_id",
            name="some_name",
            number=99
        )

        repository.insert_inventory(table)
        
        with pytest.raises(error.InventoryAlreadyExistsError):
            repository.insert_inventory(computer)

        inventories = repository.list_inventories()
        assert collections.Counter(inventories) == collections.Counter([table])