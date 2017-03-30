Feature: check subscribtion block on homepage.
  Scenario: Fill in subscribtion block.
    Given I am in the "/" path
    And I fill in "Email Address" with "someemail@sample.com"
    And I fill in "First Name" with "test_last_name"
    And I fill in "Last Name" with "test_last_name"
    And I press "Subscribe"
    Then I should see "You have been successfully subscribed."
