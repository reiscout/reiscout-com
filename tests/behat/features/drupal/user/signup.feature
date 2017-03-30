Feature: New User Signup.
  Scenario: Register new user.
    Given I go to "user/register" page
    And I fill in "E-mail address" with "someemail@sample.com"
    And I fill in "Username" with "testuser_march27"
    And I press "Create new account"
    Then I should see "You have been successfully subscribed."
