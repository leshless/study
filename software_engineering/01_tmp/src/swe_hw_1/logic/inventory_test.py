import pytest
import mock
from swe_hw_1.logic import *
import swe_hw_1.domain.model as model
import swe_hw_1.domain.error as error

@pytest.fixture
def mock_repository():
    return mock.Mock()

@pytest.fixture
def mock_rng():
    return mock.Mock()

@pytest.fixture
def inventory_controller(
    mock_rng, 
    mock_repository, 
):
    return InventoryControllerImpl(mock_rng, mock_repository)


class TestInventoryController:
    def test_create_inventory_happy_path(
            self,
            inventory_controller: InventoryController,
            mock_repository: mock.Mock,
            mock_rng: mock.Mock
    ):
        args = CreateInventoryArgs(model.InventoryType.TABLE, "some_name", 1)
        alive = model.Table("some_id", "some_name", 1)

        mock_rng.ulid.return_value = "some_id"

        res = inventory_controller.create_inventory(args)

        assert res == CreateInventoryRes("some_id")
        mock_repository.insert_inventory.assert_called_with(alive)

    def test_create_inventory_unknown_type(
            self,
            inventory_controller: InventoryController,
            mock_repository: mock.Mock,
            mock_rng: mock.Mock
    ):
        args = CreateInventoryArgs("wtf", "some_name", 1)

        mock_rng.ulid.return_value = "some_id"

        with pytest.raises(error.UnkownInventoryTypeError):
            inventory_controller.create_inventory(args)

        mock_repository.insert_inventory.assert_not_called()

    def test_list_inventories_happy_path(
            self,
            inventory_controller: InventoryController,
            mock_repository: mock.Mock,
    ):
        args = ListInventoriesArgs()
        inventories = [
            model.Thing("some_id1", "some_name1", 10), 
            model.Computer("some_id2", "some_name2", 11)
        ]

        mock_repository.list_inventories.return_value = inventories

        res = inventory_controller.list_inventories(args)
        assert res == ListInventoriesRes(inventories)
