import pytest
import mock
from swe_hw_1.logic import *
import swe_hw_1.domain.model as model
import swe_hw_1.domain.error as error

@pytest.fixture
def mock_health_controller():
    return mock.Mock()

@pytest.fixture
def mock_repository():
    return mock.Mock()

@pytest.fixture
def mock_rng():
    return mock.Mock()

@pytest.fixture
def alive_controller(
    mock_rng, 
    mock_repository, 
    mock_health_controller
):
    return AliveControllerImpl(mock_health_controller, mock_repository, mock_rng)


class TestAliveController:
    def test_create_alive_happy_path(
            self,
            alive_controller: AliveController,
            mock_health_controller: mock.Mock,
            mock_repository: mock.Mock,
            mock_rng: mock.Mock
    ):
        args = CreateAliveArgs(model.AliveType.TIGER, "some_name", 10, None)
        alive = model.Tiger("some_id", "some_name", 10)

        mock_rng.ulid.return_value = "some_id"
        mock_health_controller.check_alive_health.return_value = CheckAliveHealthRes(True)

        res = alive_controller.create_alive(args)

        assert res == CreateAliveRes("some_id")
        mock_repository.insert_alive.assert_called_with(alive)

    def test_create_alive_not_healthy(
            self,
            alive_controller: AliveController,
            mock_health_controller: mock.Mock,
            mock_repository: mock.Mock,
            mock_rng: mock.Mock
    ):
        args = CreateAliveArgs(model.AliveType.TIGER, "some_name", 10, None)

        mock_rng.ulid.return_value = "some_id"
        mock_health_controller.check_alive_health.return_value = CheckAliveHealthRes(False)

        with pytest.raises(error.AliveIsNotHealthyError):
            alive_controller.create_alive(args)

        mock_repository.insert_alive.assert_not_called()

    def test_create_alive_unknown_type(
            self,
            alive_controller: AliveController,
            mock_repository: mock.Mock,
            mock_rng: mock.Mock
    ):
        args = CreateAliveArgs("wtf", "some_name", 10, None)

        mock_rng.ulid.return_value = "some_id"

        with pytest.raises(error.UnkownAliveTypeError):
            alive_controller.create_alive(args)

        mock_repository.insert_alive.assert_not_called()
    
    def test_list_alives_happy_path(
            self,
            alive_controller: AliveController,
            mock_repository: mock.Mock
    ):
        args = ListAlivesArgs(False)
        alives = [
            model.Tiger("some_id1", "some_name1", 10), 
            model.Rabbit("some_id2", "some_name2", 5, 3)
        ]

        mock_repository.list_alives.return_value = alives

        res = alive_controller.list_alives(args)
        assert res == ListAlivesRes(alives)

    def test_list_alives_only_contact(
            self,
            alive_controller: AliveController,
            mock_repository: mock.Mock
    ):
        args = ListAlivesArgs(True)
        alives = [
            model.Tiger("some_id1", "some_name1", 10), 
            model.Rabbit("some_id2", "some_name2", 5, 3),
            model.Rabbit("some_id3", "some_name2", 5, 7),
        ]
        

        mock_repository.list_alives.return_value = alives

        res = alive_controller.list_alives(args)
        assert res == ListAlivesRes([alives[2]])

    def test_get_alives_food_consumption_happy_path(
            self,
            alive_controller: AliveController,
            mock_repository: mock.Mock
    ):
        args = ListAlivesArgs(True)
        alives = [
            model.Tiger("some_id1", "some_name1", 10), 
            model.Rabbit("some_id2", "some_name2", 5, 3),
            model.Rabbit("some_id3", "some_name2", 5, 7),
        ]

        mock_repository.list_alives.return_value = alives

        res = alive_controller.get_alives_food_consumption(args)
        assert res == GetAlivesFoodConsumptionRes(20)