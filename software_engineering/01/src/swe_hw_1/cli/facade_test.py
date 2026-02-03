import pytest
import mock
from swe_hw_1.cli import *
import swe_hw_1.domain.model as model
import swe_hw_1.domain.error as error
import swe_hw_1.logic as logic

@pytest.fixture
def mock_alive_controller():
    return mock.Mock()

@pytest.fixture
def mock_inventory_controller():
    return mock.Mock()

@pytest.fixture
def facade(mock_alive_controller, mock_inventory_controller):
    return FacadeImpl(mock_alive_controller, mock_inventory_controller)

class TestFacade:
    def test_create_alive_happy_path(
        self,
        facade: Facade,
        mock_alive_controller: logic.AliveController,
    ):
        request = CreateAliveRequest("RABBIT", "some_name", 9, 5)
        args = logic.CreateAliveArgs(model.AliveType.RABBIT, "some_name", 9, 5)

        mock_alive_controller.create_alive.return_value = logic.CreateAliveRes("some_id")

        response = facade.create_alive(request)

        assert response == "Sucessfully created new animal some_id"
        mock_alive_controller.create_alive.assert_called_with(args)
