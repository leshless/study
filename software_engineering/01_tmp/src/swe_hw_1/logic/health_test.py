import pytest
import mock
from swe_hw_1.logic import *
import swe_hw_1.domain.model as model
import swe_hw_1.domain.error as error

@pytest.fixture
def mock_rng():
    return mock.Mock()

@pytest.fixture
def health_controller(mock_rng):
    return HealthControllerImpl(mock_rng)


class TestHealthController:
    def test_check_alive_health_happy_path(
            self,
            health_controller: HealthController,
            mock_rng: mock.Mock
    ):
        alive = model.Tiger("some_id", "some_name", 10)
        args = CheckAliveHealthArgs(alive)

        mock_rng.is_occured.return_value = True

        res = health_controller.check_alive_health(args)

        assert res == CheckAliveHealthRes(True)
        mock_rng.is_occured.assert_called_with(ALIVE_HEALTHNESS_PROBABILITY)

    def test_check_alive_health_not_healthy(
            self,
            health_controller: HealthController,
            mock_rng: mock.Mock
    ):
        alive = model.Tiger("some_id", "some_name", 10)
        args = CheckAliveHealthArgs(alive)

        mock_rng.is_occured.return_value = False

        res = health_controller.check_alive_health(args)

        assert res == CheckAliveHealthRes(False)
        mock_rng.is_occured.assert_called_with(ALIVE_HEALTHNESS_PROBABILITY)

 